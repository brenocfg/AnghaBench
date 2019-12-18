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
typedef  int u8 ;
typedef  int u16 ;
struct dtv_frontend_properties {int transmission_mode; int guard_interval; int modulation; int hierarchy; int code_rate_HP; int code_rate_LP; int /*<<< orphan*/  bandwidth_hz; } ;
struct dib7000m_state {int reg_offs; int div_sync_wait; int revision; int div_force_off; int /*<<< orphan*/  div_state; int /*<<< orphan*/  demod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD ; 
#define  FEC_1_2 145 
#define  FEC_2_3 144 
#define  FEC_3_4 143 
#define  FEC_5_6 142 
#define  FEC_7_8 141 
#define  GUARD_INTERVAL_1_16 140 
#define  GUARD_INTERVAL_1_32 139 
#define  GUARD_INTERVAL_1_4 138 
#define  GUARD_INTERVAL_1_8 137 
#define  HIERARCHY_1 136 
#define  HIERARCHY_2 135 
#define  HIERARCHY_4 134 
#define  QAM_16 133 
#define  QAM_64 132 
#define  QPSK 131 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int /*<<< orphan*/  dib7000m_set_bandwidth (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_diversity_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_power_mode (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int) ; 

__attribute__((used)) static void dib7000m_set_channel(struct dib7000m_state *state, struct dtv_frontend_properties *ch,
				 u8 seq)
{
	u16 value, est[4];

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	/* nfft, guard, qam, alpha */
	value = 0;
	switch (ch->transmission_mode) {
		case TRANSMISSION_MODE_2K: value |= (0 << 7); break;
		case TRANSMISSION_MODE_4K: value |= (2 << 7); break;
		default:
		case TRANSMISSION_MODE_8K: value |= (1 << 7); break;
	}
	switch (ch->guard_interval) {
		case GUARD_INTERVAL_1_32: value |= (0 << 5); break;
		case GUARD_INTERVAL_1_16: value |= (1 << 5); break;
		case GUARD_INTERVAL_1_4:  value |= (3 << 5); break;
		default:
		case GUARD_INTERVAL_1_8:  value |= (2 << 5); break;
	}
	switch (ch->modulation) {
		case QPSK:  value |= (0 << 3); break;
		case QAM_16: value |= (1 << 3); break;
		default:
		case QAM_64: value |= (2 << 3); break;
	}
	switch (HIERARCHY_1) {
		case HIERARCHY_2: value |= 2; break;
		case HIERARCHY_4: value |= 4; break;
		default:
		case HIERARCHY_1: value |= 1; break;
	}
	dib7000m_write_word(state, 0, value);
	dib7000m_write_word(state, 5, (seq << 4));

	/* P_dintl_native, P_dintlv_inv, P_hrch, P_code_rate, P_select_hp */
	value = 0;
	if (1 != 0)
		value |= (1 << 6);
	if (ch->hierarchy == 1)
		value |= (1 << 4);
	if (1 == 1)
		value |= 1;
	switch ((ch->hierarchy == 0 || 1 == 1) ? ch->code_rate_HP : ch->code_rate_LP) {
		case FEC_2_3: value |= (2 << 1); break;
		case FEC_3_4: value |= (3 << 1); break;
		case FEC_5_6: value |= (5 << 1); break;
		case FEC_7_8: value |= (7 << 1); break;
		default:
		case FEC_1_2: value |= (1 << 1); break;
	}
	dib7000m_write_word(state, 267 + state->reg_offs, value);

	/* offset loop parameters */

	/* P_timf_alpha = 6, P_corm_alpha=6, P_corm_thres=0x80 */
	dib7000m_write_word(state, 26, (6 << 12) | (6 << 8) | 0x80);

	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=1, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	dib7000m_write_word(state, 29, (0 << 14) | (4 << 10) | (1 << 9) | (3 << 5) | (1 << 4) | (0x3));

	/* P_ctrl_freeze_pha_shift=0, P_ctrl_pha_off_max=3 */
	dib7000m_write_word(state, 32, (0 << 4) | 0x3);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step=5 */
	dib7000m_write_word(state, 33, (0 << 4) | 0x5);

	/* P_dvsy_sync_wait */
	switch (ch->transmission_mode) {
		case TRANSMISSION_MODE_8K: value = 256; break;
		case TRANSMISSION_MODE_4K: value = 128; break;
		case TRANSMISSION_MODE_2K:
		default: value = 64; break;
	}
	switch (ch->guard_interval) {
		case GUARD_INTERVAL_1_16: value *= 2; break;
		case GUARD_INTERVAL_1_8:  value *= 4; break;
		case GUARD_INTERVAL_1_4:  value *= 8; break;
		default:
		case GUARD_INTERVAL_1_32: value *= 1; break;
	}
	state->div_sync_wait = (value * 3) / 2 + 32; // add 50% SFN margin + compensate for one DVSY-fifo TODO

	/* deactivate the possibility of diversity reception if extended interleave - not for 7000MC */
	/* P_dvsy_sync_mode = 0, P_dvsy_sync_enable=1, P_dvcb_comb_mode=2 */
	if (1 == 1 || state->revision > 0x4000)
		state->div_force_off = 0;
	else
		state->div_force_off = 1;
	dib7000m_set_diversity_in(&state->demod, state->div_state);

	/* channel estimation fine configuration */
	switch (ch->modulation) {
		case QAM_64:
			est[0] = 0x0148;       /* P_adp_regul_cnt 0.04 */
			est[1] = 0xfff0;       /* P_adp_noise_cnt -0.002 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.001 */
			break;
		case QAM_16:
			est[0] = 0x023d;       /* P_adp_regul_cnt 0.07 */
			est[1] = 0xffdf;       /* P_adp_noise_cnt -0.004 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff0;       /* P_adp_noise_ext -0.002 */
			break;
		default:
			est[0] = 0x099a;       /* P_adp_regul_cnt 0.3 */
			est[1] = 0xffae;       /* P_adp_noise_cnt -0.01 */
			est[2] = 0x0333;       /* P_adp_regul_ext 0.1 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.002 */
			break;
	}
	for (value = 0; value < 4; value++)
		dib7000m_write_word(state, 214 + value + state->reg_offs, est[value]);

	// set power-up level: autosearch
	dib7000m_set_power_mode(state, DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD);
}