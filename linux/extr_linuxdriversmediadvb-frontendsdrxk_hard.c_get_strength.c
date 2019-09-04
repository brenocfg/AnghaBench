#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct s_cfg_agc {scalar_t__ ctrl_mode; int output_level; scalar_t__ min_output_level; scalar_t__ max_output_level; int top; } ;
struct drxk_state {struct s_cfg_agc m_atv_if_agc_cfg; struct s_cfg_agc m_atv_rf_agc_cfg; struct s_cfg_agc m_qam_if_agc_cfg; struct s_cfg_agc m_qam_rf_agc_cfg; struct s_cfg_agc m_dvbt_if_agc_cfg; struct s_cfg_agc m_dvbt_rf_agc_cfg; } ;

/* Variables and functions */
 scalar_t__ DRXK_AGC_CTRL_AUTO ; 
 int /*<<< orphan*/  SCU_RAM_AGC_IF_IACCU_HI__A ; 
 int /*<<< orphan*/  SCU_RAM_AGC_INGAIN_TGT_MIN__A ; 
 int /*<<< orphan*/  SCU_RAM_AGC_RF_IACCU_HI_CO__A ; 
 int /*<<< orphan*/  SCU_RAM_AGC_RF_IACCU_HI__A ; 
 scalar_t__ is_dvbt (struct drxk_state*) ; 
 scalar_t__ is_qam (struct drxk_state*) ; 
 int read16 (struct drxk_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_strength(struct drxk_state *state, u64 *strength)
{
	int status;
	struct s_cfg_agc   rf_agc, if_agc;
	u32          total_gain  = 0;
	u32          atten      = 0;
	u32          agc_range   = 0;
	u16            scu_lvl  = 0;
	u16            scu_coc  = 0;
	/* FIXME: those are part of the tuner presets */
	u16 tuner_rf_gain         = 50; /* Default value on az6007 driver */
	u16 tuner_if_gain         = 40; /* Default value on az6007 driver */

	*strength = 0;

	if (is_dvbt(state)) {
		rf_agc = state->m_dvbt_rf_agc_cfg;
		if_agc = state->m_dvbt_if_agc_cfg;
	} else if (is_qam(state)) {
		rf_agc = state->m_qam_rf_agc_cfg;
		if_agc = state->m_qam_if_agc_cfg;
	} else {
		rf_agc = state->m_atv_rf_agc_cfg;
		if_agc = state->m_atv_if_agc_cfg;
	}

	if (rf_agc.ctrl_mode == DRXK_AGC_CTRL_AUTO) {
		/* SCU output_level */
		status = read16(state, SCU_RAM_AGC_RF_IACCU_HI__A, &scu_lvl);
		if (status < 0)
			return status;

		/* SCU c.o.c. */
		status = read16(state, SCU_RAM_AGC_RF_IACCU_HI_CO__A, &scu_coc);
		if (status < 0)
			return status;

		if (((u32) scu_lvl + (u32) scu_coc) < 0xffff)
			rf_agc.output_level = scu_lvl + scu_coc;
		else
			rf_agc.output_level = 0xffff;

		/* Take RF gain into account */
		total_gain += tuner_rf_gain;

		/* clip output value */
		if (rf_agc.output_level < rf_agc.min_output_level)
			rf_agc.output_level = rf_agc.min_output_level;
		if (rf_agc.output_level > rf_agc.max_output_level)
			rf_agc.output_level = rf_agc.max_output_level;

		agc_range = (u32) (rf_agc.max_output_level - rf_agc.min_output_level);
		if (agc_range > 0) {
			atten += 100UL *
				((u32)(tuner_rf_gain)) *
				((u32)(rf_agc.output_level - rf_agc.min_output_level))
				/ agc_range;
		}
	}

	if (if_agc.ctrl_mode == DRXK_AGC_CTRL_AUTO) {
		status = read16(state, SCU_RAM_AGC_IF_IACCU_HI__A,
				&if_agc.output_level);
		if (status < 0)
			return status;

		status = read16(state, SCU_RAM_AGC_INGAIN_TGT_MIN__A,
				&if_agc.top);
		if (status < 0)
			return status;

		/* Take IF gain into account */
		total_gain += (u32) tuner_if_gain;

		/* clip output value */
		if (if_agc.output_level < if_agc.min_output_level)
			if_agc.output_level = if_agc.min_output_level;
		if (if_agc.output_level > if_agc.max_output_level)
			if_agc.output_level = if_agc.max_output_level;

		agc_range  = (u32)(if_agc.max_output_level - if_agc.min_output_level);
		if (agc_range > 0) {
			atten += 100UL *
				((u32)(tuner_if_gain)) *
				((u32)(if_agc.output_level - if_agc.min_output_level))
				/ agc_range;
		}
	}

	/*
	 * Convert to 0..65535 scale.
	 * If it can't be measured (AGC is disabled), just show 100%.
	 */
	if (total_gain > 0)
		*strength = (65535UL * atten / total_gain / 100);
	else
		*strength = 65535;

	return 0;
}