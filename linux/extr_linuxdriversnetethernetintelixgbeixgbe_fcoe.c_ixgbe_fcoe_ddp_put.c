#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct net_device {size_t fcoe_ddp_xid; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_fcoe_ddp {int len; int /*<<< orphan*/ * pool; int /*<<< orphan*/  udp; int /*<<< orphan*/  udl; int /*<<< orphan*/  sgc; scalar_t__ sgl; int /*<<< orphan*/  err; } ;
struct ixgbe_fcoe {int /*<<< orphan*/  lock; struct ixgbe_fcoe_ddp* ddp; } ;
struct ixgbe_adapter {TYPE_2__* pdev; struct ixgbe_hw hw; struct ixgbe_fcoe fcoe; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IXGBE_FCBUFF ; 
 int IXGBE_FCBUFF_VALID ; 
 int /*<<< orphan*/  IXGBE_FCDDC (int,size_t) ; 
 int /*<<< orphan*/  IXGBE_FCDFC (int,size_t) ; 
 int /*<<< orphan*/  IXGBE_FCDMARW ; 
 size_t IXGBE_FCDMARW_RE ; 
 size_t IXGBE_FCDMARW_WE ; 
 int /*<<< orphan*/  IXGBE_FCFLT ; 
 int /*<<< orphan*/  IXGBE_FCFLTRW ; 
 size_t IXGBE_FCFLTRW_WE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_fcoe_clear_ddp (struct ixgbe_fcoe_ddp*) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int ixgbe_fcoe_ddp_put(struct net_device *netdev, u16 xid)
{
	int len;
	struct ixgbe_fcoe *fcoe;
	struct ixgbe_adapter *adapter;
	struct ixgbe_fcoe_ddp *ddp;
	struct ixgbe_hw *hw;
	u32 fcbuff;

	if (!netdev)
		return 0;

	if (xid >= netdev->fcoe_ddp_xid)
		return 0;

	adapter = netdev_priv(netdev);
	fcoe = &adapter->fcoe;
	ddp = &fcoe->ddp[xid];
	if (!ddp->udl)
		return 0;

	hw = &adapter->hw;
	len = ddp->len;
	/* if no error then skip ddp context invalidation */
	if (!ddp->err)
		goto skip_ddpinv;

	if (hw->mac.type == ixgbe_mac_X550) {
		/* X550 does not require DDP FCoE lock */

		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(0, xid), 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(3, xid),
				(xid | IXGBE_FCFLTRW_WE));

		/* program FCBUFF */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(2, xid), 0);

		/* program FCDMARW */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(3, xid),
				(xid | IXGBE_FCDMARW_WE));

		/* read FCBUFF to check context invalidated */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(3, xid),
				(xid | IXGBE_FCDMARW_RE));
		fcbuff = IXGBE_READ_REG(hw, IXGBE_FCDDC(2, xid));
	} else {
		/* other hardware requires DDP FCoE lock */
		spin_lock_bh(&fcoe->lock);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLT, 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLTRW,
				(xid | IXGBE_FCFLTRW_WE));
		IXGBE_WRITE_REG(hw, IXGBE_FCBUFF, 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_WE));

		/* guaranteed to be invalidated after 100us */
		IXGBE_WRITE_REG(hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_RE));
		fcbuff = IXGBE_READ_REG(hw, IXGBE_FCBUFF);
		spin_unlock_bh(&fcoe->lock);
		}

	if (fcbuff & IXGBE_FCBUFF_VALID)
		usleep_range(100, 150);

skip_ddpinv:
	if (ddp->sgl)
		dma_unmap_sg(&adapter->pdev->dev, ddp->sgl, ddp->sgc,
			     DMA_FROM_DEVICE);
	if (ddp->pool) {
		dma_pool_free(ddp->pool, ddp->udl, ddp->udp);
		ddp->pool = NULL;
	}

	ixgbe_fcoe_clear_ddp(ddp);

	return len;
}