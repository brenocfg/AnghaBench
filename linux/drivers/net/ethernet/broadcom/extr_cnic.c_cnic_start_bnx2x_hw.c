#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int* pg_map_arr; } ;
struct TYPE_6__ {int* pg_map_arr; } ;
struct TYPE_7__ {TYPE_2__ dma; scalar_t__ io_addr; } ;
struct cnic_local {TYPE_4__ gbl_buf_info; int /*<<< orphan*/  status_blk_num; TYPE_3__ kcq1; int /*<<< orphan*/  bnx2x_igu_sb_id; int /*<<< orphan*/  fcoe_start_cid; int /*<<< orphan*/  fcoe_cid_tbl; int /*<<< orphan*/  iscsi_start_cid; int /*<<< orphan*/  cid_tbl; int /*<<< orphan*/  func; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int /*<<< orphan*/  drv_state; TYPE_1__* irq_arr; int /*<<< orphan*/  addr_drv_info_to_mcp; } ;
struct cnic_dev {int /*<<< orphan*/  max_fcoe_conn; int /*<<< orphan*/  stats_addr; int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int /*<<< orphan*/  pfid; int /*<<< orphan*/  pf_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  status_blk_num2; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BNX2X_CHIP_IS_E2_PLUS (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_DRV_STATE_HANDLES_IRQ ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  CNIC_WR16 (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNIC_WR8 (struct cnic_dev*,scalar_t__,int) ; 
 scalar_t__ CSTORM_ISCSI_EQ_CONS_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_EQ_NEXT_EQE_ADDR_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_VALID_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_EQ_SB_INDEX_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_ISCSI_EQ_SB_NUM_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DEF_RCV_BUF ; 
 int ENOMEM ; 
 int HC_INDEX_ISCSI_EQ_CONS ; 
 int /*<<< orphan*/  MAX_ISCSI_TBL_SZ ; 
 int /*<<< orphan*/  MAX_KCQ_IDX ; 
 scalar_t__ TSTORM_ISCSI_TCP_LOCAL_ADV_WND_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_ISCSI_GLOBAL_BUF_PHYS_ADDR_OFFSET (int /*<<< orphan*/ ) ; 
 int cnic_init_bnx2x_irq (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_init_bnx2x_kcq (struct cnic_dev*) ; 
 int cnic_init_id_tbl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_setup_bnx2x_context (struct cnic_dev*) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_start_bnx2x_hw(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	struct cnic_eth_dev *ethdev = cp->ethdev;
	int ret;
	u32 pfid;

	dev->stats_addr = ethdev->addr_drv_info_to_mcp;
	cp->func = bp->pf_num;

	pfid = bp->pfid;

	ret = cnic_init_id_tbl(&cp->cid_tbl, MAX_ISCSI_TBL_SZ,
			       cp->iscsi_start_cid, 0);

	if (ret)
		return -ENOMEM;

	if (BNX2X_CHIP_IS_E2_PLUS(bp)) {
		ret = cnic_init_id_tbl(&cp->fcoe_cid_tbl, dev->max_fcoe_conn,
					cp->fcoe_start_cid, 0);

		if (ret)
			return -ENOMEM;
	}

	cp->bnx2x_igu_sb_id = ethdev->irq_arr[0].status_blk_num2;

	cnic_init_bnx2x_kcq(dev);

	/* Only 1 EQ */
	CNIC_WR16(dev, cp->kcq1.io_addr, MAX_KCQ_IDX);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_CONS_OFFSET(pfid, 0), 0);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_OFFSET(pfid, 0),
		cp->kcq1.dma.pg_map_arr[1] & 0xffffffff);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_OFFSET(pfid, 0) + 4,
		(u64) cp->kcq1.dma.pg_map_arr[1] >> 32);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_EQE_ADDR_OFFSET(pfid, 0),
		cp->kcq1.dma.pg_map_arr[0] & 0xffffffff);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_EQE_ADDR_OFFSET(pfid, 0) + 4,
		(u64) cp->kcq1.dma.pg_map_arr[0] >> 32);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_VALID_OFFSET(pfid, 0), 1);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_SB_NUM_OFFSET(pfid, 0), cp->status_blk_num);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_SB_INDEX_OFFSET(pfid, 0),
		HC_INDEX_ISCSI_EQ_CONS);

	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_GLOBAL_BUF_PHYS_ADDR_OFFSET(pfid),
		cp->gbl_buf_info.pg_map_arr[0] & 0xffffffff);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_GLOBAL_BUF_PHYS_ADDR_OFFSET(pfid) + 4,
		(u64) cp->gbl_buf_info.pg_map_arr[0] >> 32);

	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_TCP_LOCAL_ADV_WND_OFFSET(pfid), DEF_RCV_BUF);

	cnic_setup_bnx2x_context(dev);

	ret = cnic_init_bnx2x_irq(dev);
	if (ret)
		return ret;

	ethdev->drv_state |= CNIC_DRV_STATE_HANDLES_IRQ;
	return 0;
}