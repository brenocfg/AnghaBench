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
struct rcb_common_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCB_COM_AXI_ERR_STS ; 
 int /*<<< orphan*/  RCB_COM_AXI_WR_ERR_INTMASK ; 
 int /*<<< orphan*/  RCB_COM_INTMASK_ECC_ERR_REG ; 
 int /*<<< orphan*/  RCB_COM_INTMSK_TX_PKT_REG ; 
 int /*<<< orphan*/  RCB_COM_INTSTS_ECC_ERR_REG ; 
 int /*<<< orphan*/  RCB_COM_RINT_TX_PKT_REG ; 
 int /*<<< orphan*/  RCB_COM_SF_CFG_BD_RINT_STS ; 
 int /*<<< orphan*/  RCB_COM_SF_CFG_INTMASK_BD ; 
 int /*<<< orphan*/  RCB_COM_SF_CFG_INTMASK_RING ; 
 int /*<<< orphan*/  RCB_COM_SF_CFG_RING_STS ; 
 int /*<<< orphan*/  dsaf_write_dev (struct rcb_common_cb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_rcb_comm_exc_irq_en(
			struct rcb_common_cb *rcb_common, int en)
{
	u32 clr_vlue = 0xfffffffful;
	u32 msk_vlue = en ? 0 : 0xfffffffful;

	/* clr int*/
	dsaf_write_dev(rcb_common, RCB_COM_INTSTS_ECC_ERR_REG, clr_vlue);

	dsaf_write_dev(rcb_common, RCB_COM_SF_CFG_RING_STS, clr_vlue);

	dsaf_write_dev(rcb_common, RCB_COM_SF_CFG_BD_RINT_STS, clr_vlue);

	dsaf_write_dev(rcb_common, RCB_COM_RINT_TX_PKT_REG, clr_vlue);
	dsaf_write_dev(rcb_common, RCB_COM_AXI_ERR_STS, clr_vlue);

	/*en msk*/
	dsaf_write_dev(rcb_common, RCB_COM_INTMASK_ECC_ERR_REG, msk_vlue);

	dsaf_write_dev(rcb_common, RCB_COM_SF_CFG_INTMASK_RING, msk_vlue);

	/*for tx bd neednot cacheline, so msk sf_txring_fbd_intmask (bit 1)**/
	dsaf_write_dev(rcb_common, RCB_COM_SF_CFG_INTMASK_BD, msk_vlue | 2);

	dsaf_write_dev(rcb_common, RCB_COM_INTMSK_TX_PKT_REG, msk_vlue);
	dsaf_write_dev(rcb_common, RCB_COM_AXI_WR_ERR_INTMASK, msk_vlue);
}