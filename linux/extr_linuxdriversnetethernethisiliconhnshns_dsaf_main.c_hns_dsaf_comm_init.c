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
typedef  scalar_t__ u32 ;
struct dsaf_device {int /*<<< orphan*/  dsaf_tc_mode; int /*<<< orphan*/  dsaf_en; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSAF_CFG_0_REG ; 
 int /*<<< orphan*/  DSAF_CFG_CRC_EN_S ; 
 int /*<<< orphan*/  DSAF_CFG_EN_S ; 
 int /*<<< orphan*/  DSAF_CFG_LOCA_ADDR_EN_S ; 
 int /*<<< orphan*/  DSAF_CFG_MIX_MODE_S ; 
 int /*<<< orphan*/  DSAF_CFG_TC_MODE_S ; 
 scalar_t__ DSAF_COMM_CHN ; 
 int /*<<< orphan*/  DSAF_DEFAUTL_QUEUE_NUM_PER_PPE ; 
 int /*<<< orphan*/  DSAF_STP_PORT_TYPE_FORWARD ; 
 int /*<<< orphan*/  DSAF_SW_PORT_TYPE_NON_VLAN ; 
 scalar_t__ dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hns_dsaf_inner_qid_cfg (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_int_ppe_msk_set (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_ppe_src_clr (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_rocee_msk_set (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_rocee_src_clr (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_tbl_msk_set (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_tbl_src_clr (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_xge_msk_set (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_int_xge_src_clr (struct dsaf_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_dsaf_mix_def_qid_cfg (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_pfc_en_cfg (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_ppe_qid_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_reg_cnt_clr_ce (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  hns_dsaf_set_pfc_pause (struct dsaf_device*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  hns_dsaf_stp_port_type_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_sw_port_type_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_comm_init(struct dsaf_device *dsaf_dev)
{
	u32 i;
	u32 o_dsaf_cfg;
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	o_dsaf_cfg = dsaf_read_dev(dsaf_dev, DSAF_CFG_0_REG);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_EN_S, dsaf_dev->dsaf_en);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_TC_MODE_S, dsaf_dev->dsaf_tc_mode);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_CRC_EN_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_MIX_MODE_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_LOCA_ADDR_EN_S, 0);
	dsaf_write_dev(dsaf_dev, DSAF_CFG_0_REG, o_dsaf_cfg);

	hns_dsaf_reg_cnt_clr_ce(dsaf_dev, 1);
	hns_dsaf_stp_port_type_cfg(dsaf_dev, DSAF_STP_PORT_TYPE_FORWARD);

	/* set 22 queue per tx ppe engine, only used in switch mode */
	hns_dsaf_ppe_qid_cfg(dsaf_dev, DSAF_DEFAUTL_QUEUE_NUM_PER_PPE);

	/* set promisc def queue id */
	hns_dsaf_mix_def_qid_cfg(dsaf_dev);

	/* set inner loopback queue id */
	hns_dsaf_inner_qid_cfg(dsaf_dev);

	/* in non switch mode, set all port to access mode */
	hns_dsaf_sw_port_type_cfg(dsaf_dev, DSAF_SW_PORT_TYPE_NON_VLAN);

	/*set dsaf pfc  to 0 for parseing rx pause*/
	for (i = 0; i < DSAF_COMM_CHN; i++) {
		hns_dsaf_pfc_en_cfg(dsaf_dev, i, 0);
		hns_dsaf_set_pfc_pause(dsaf_dev, i, is_ver1, is_ver1);
	}

	/*msk and  clr exception irqs */
	for (i = 0; i < DSAF_COMM_CHN; i++) {
		hns_dsaf_int_xge_src_clr(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_int_ppe_src_clr(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_int_rocee_src_clr(dsaf_dev, i, 0xfffffffful);

		hns_dsaf_int_xge_msk_set(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_int_ppe_msk_set(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_int_rocee_msk_set(dsaf_dev, i, 0xfffffffful);
	}
	hns_dsaf_int_tbl_src_clr(dsaf_dev, 0xfffffffful);
	hns_dsaf_int_tbl_msk_set(dsaf_dev, 0xfffffffful);
}