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
typedef  int u32 ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int DASFV2_ROCEE_CRD_NUM ; 
 int DSAFV2_SBM_BP_CFG_2_ROCEE_REG_0_REG ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_RESET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_RESET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_SET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG2_SET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_S ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_S ; 
 int DSAFV2_SBM_PPE_CHN ; 
 int DSAFV2_SBM_XGE_CHN ; 
 int DSAF_SBM_BP_CFG_0_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_1_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_PPE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_3_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_4_REG_0_REG ; 
 int dsaf_read_dev (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  dsaf_set_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int,int) ; 

__attribute__((used)) static void hns_dsafv2_sbm_bp_wl_cfg(struct dsaf_device *dsaf_dev)
{
	u32 o_sbm_bp_cfg;
	u32 reg;
	u32 i;

	/* XGE */
	for (i = 0; i < DSAFV2_SBM_XGE_CHN; i++) {
		reg = DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_S, 256);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_1_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_RESET_BUF_NUM_S, 128);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_3_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 55);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 110);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		/* for no enable pfc mode */
		reg = DSAF_SBM_BP_CFG_4_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}

	/* PPE */
	for (i = 0; i < DSAFV2_SBM_PPE_CHN; i++) {
		reg = DSAF_SBM_BP_CFG_2_PPE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_S, 3);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_S, 52);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}

	/* RoCEE */
	for (i = 0; i < DASFV2_ROCEE_CRD_NUM; i++) {
		reg = DSAFV2_SBM_BP_CFG_2_ROCEE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_S, 4);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}
}