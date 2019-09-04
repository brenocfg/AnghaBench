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
 int DSAF_COMM_CHN ; 
 int DSAF_SBM_BP_CFG_0_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_1_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_PPE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_ROCEE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_3_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_4_REG_0_REG ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_COM_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_COM_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG2_RESET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG2_RESET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG2_SET_BUF_NUM_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG2_SET_BUF_NUM_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S ; 
 int /*<<< orphan*/  DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M ; 
 int /*<<< orphan*/  DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S ; 
 int DSAF_XGE_NUM ; 
 int dsaf_read_dev (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  dsaf_set_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int,int) ; 

__attribute__((used)) static void hns_dsaf_sbm_bp_wl_cfg(struct dsaf_device *dsaf_dev)
{
	u32 o_sbm_bp_cfg;
	u32 reg;
	u32 i;

	/* XGE */
	for (i = 0; i < DSAF_XGE_NUM; i++) {
		reg = DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_COM_MAX_BUF_NUM_S, 512);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_1_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 128);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_3_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 110);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 160);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		/* for no enable pfc mode */
		reg = DSAF_SBM_BP_CFG_4_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}

	/* PPE */
	for (i = 0; i < DSAF_COMM_CHN; i++) {
		reg = DSAF_SBM_BP_CFG_2_PPE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 10);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 12);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}

	/* RoCEE */
	for (i = 0; i < DSAF_COMM_CHN; i++) {
		reg = DSAF_SBM_BP_CFG_2_ROCEE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_read_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 4);
		dsaf_write_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	}
}