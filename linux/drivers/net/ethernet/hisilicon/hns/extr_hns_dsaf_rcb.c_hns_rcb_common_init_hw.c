#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rcb_common_cb {TYPE_1__* dsaf_dev; int /*<<< orphan*/  desc_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  dsaf_ver; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (TYPE_1__*) ; 
 int HNS_RCB_COMMON_ENDIAN ; 
 int /*<<< orphan*/  HNS_RCB_DEF_COALESCED_USECS ; 
 int /*<<< orphan*/  HNS_RCB_DEF_RX_COALESCED_FRAMES ; 
 int /*<<< orphan*/  HNS_RCB_DEF_TX_COALESCED_FRAMES ; 
 int HNS_TSO_MODE_8BD_32K ; 
 int /*<<< orphan*/  RCBV2_COM_CFG_TSO_MODE_REG ; 
 int /*<<< orphan*/  RCBV2_COM_CFG_USER_REG ; 
 int /*<<< orphan*/  RCB_COM_CFG_ENDIAN_REG ; 
 int /*<<< orphan*/  RCB_COM_CFG_FA_B ; 
 int /*<<< orphan*/  RCB_COM_CFG_FA_REG ; 
 int /*<<< orphan*/  RCB_COM_CFG_FNA_B ; 
 int /*<<< orphan*/  RCB_COM_CFG_FNA_REG ; 
 int /*<<< orphan*/  RCB_COM_CFG_INIT_FLAG_REG ; 
 int /*<<< orphan*/  RCB_COM_TSO_MODE_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dsaf_read_dev (struct rcb_common_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct rcb_common_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct rcb_common_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcb_comm_exc_irq_en (struct rcb_common_cb*,int /*<<< orphan*/ ) ; 
 int hns_rcb_common_get_port_num (struct rcb_common_cb*) ; 
 int /*<<< orphan*/  hns_rcb_set_port_desc_cnt (struct rcb_common_cb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_set_port_timeout (struct rcb_common_cb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_set_rx_coalesced_frames (struct rcb_common_cb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_set_tx_coalesced_frames (struct rcb_common_cb*,int,int /*<<< orphan*/ ) ; 

int hns_rcb_common_init_hw(struct rcb_common_cb *rcb_common)
{
	u32 reg_val;
	int i;
	int port_num = hns_rcb_common_get_port_num(rcb_common);

	hns_rcb_comm_exc_irq_en(rcb_common, 0);

	reg_val = dsaf_read_dev(rcb_common, RCB_COM_CFG_INIT_FLAG_REG);
	if (0x1 != (reg_val & 0x1)) {
		dev_err(rcb_common->dsaf_dev->dev,
			"RCB_COM_CFG_INIT_FLAG_REG reg = 0x%x\n", reg_val);
		return -EBUSY;
	}

	for (i = 0; i < port_num; i++) {
		hns_rcb_set_port_desc_cnt(rcb_common, i, rcb_common->desc_num);
		hns_rcb_set_rx_coalesced_frames(
			rcb_common, i, HNS_RCB_DEF_RX_COALESCED_FRAMES);
		if (!AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver) &&
		    !HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
			hns_rcb_set_tx_coalesced_frames(
				rcb_common, i, HNS_RCB_DEF_TX_COALESCED_FRAMES);
		hns_rcb_set_port_timeout(
			rcb_common, i, HNS_RCB_DEF_COALESCED_USECS);
	}

	dsaf_write_dev(rcb_common, RCB_COM_CFG_ENDIAN_REG,
		       HNS_RCB_COMMON_ENDIAN);

	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) {
		dsaf_write_dev(rcb_common, RCB_COM_CFG_FNA_REG, 0x0);
		dsaf_write_dev(rcb_common, RCB_COM_CFG_FA_REG, 0x1);
	} else {
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FNA_B, false);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FA_B, true);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_TSO_MODE_REG,
				 RCB_COM_TSO_MODE_B, HNS_TSO_MODE_8BD_32K);
	}

	return 0;
}