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
struct TYPE_4__ {int btr_ts2_shift; int btr_sjw_shift; scalar_t__ cantype; } ;
struct can_bittiming {int brp; int prop_seg; int phase_seg1; int phase_seg2; int sjw; } ;
struct TYPE_3__ {struct can_bittiming data_bittiming; struct can_bittiming bittiming; } ;
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;TYPE_2__ devtype; TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ XAXI_CANFD ; 
 scalar_t__ XAXI_CANFD_2_0 ; 
 int /*<<< orphan*/  XCAN_BRPR_OFFSET ; 
 int /*<<< orphan*/  XCAN_BTR_OFFSET ; 
 int /*<<< orphan*/  XCAN_F_BRPR_OFFSET ; 
 int /*<<< orphan*/  XCAN_F_BTR_OFFSET ; 
 int XCAN_SR_CONFIG_MASK ; 
 int /*<<< orphan*/  XCAN_SR_OFFSET ; 
 int /*<<< orphan*/  netdev_alert (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int stub6 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int stub7 (struct xcan_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcan_set_bittiming(struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	struct can_bittiming *bt = &priv->can.bittiming;
	struct can_bittiming *dbt = &priv->can.data_bittiming;
	u32 btr0, btr1;
	u32 is_config_mode;

	/* Check whether Xilinx CAN is in configuration mode.
	 * It cannot set bit timing if Xilinx CAN is not in configuration mode.
	 */
	is_config_mode = priv->read_reg(priv, XCAN_SR_OFFSET) &
				XCAN_SR_CONFIG_MASK;
	if (!is_config_mode) {
		netdev_alert(ndev,
		     "BUG! Cannot set bittiming - CAN is not in config mode\n");
		return -EPERM;
	}

	/* Setting Baud Rate prescalar value in BRPR Register */
	btr0 = (bt->brp - 1);

	/* Setting Time Segment 1 in BTR Register */
	btr1 = (bt->prop_seg + bt->phase_seg1 - 1);

	/* Setting Time Segment 2 in BTR Register */
	btr1 |= (bt->phase_seg2 - 1) << priv->devtype.btr_ts2_shift;

	/* Setting Synchronous jump width in BTR Register */
	btr1 |= (bt->sjw - 1) << priv->devtype.btr_sjw_shift;

	priv->write_reg(priv, XCAN_BRPR_OFFSET, btr0);
	priv->write_reg(priv, XCAN_BTR_OFFSET, btr1);

	if (priv->devtype.cantype == XAXI_CANFD ||
	    priv->devtype.cantype == XAXI_CANFD_2_0) {
		/* Setting Baud Rate prescalar value in F_BRPR Register */
		btr0 = dbt->brp - 1;

		/* Setting Time Segment 1 in BTR Register */
		btr1 = dbt->prop_seg + dbt->phase_seg1 - 1;

		/* Setting Time Segment 2 in BTR Register */
		btr1 |= (dbt->phase_seg2 - 1) << priv->devtype.btr_ts2_shift;

		/* Setting Synchronous jump width in BTR Register */
		btr1 |= (dbt->sjw - 1) << priv->devtype.btr_sjw_shift;

		priv->write_reg(priv, XCAN_F_BRPR_OFFSET, btr0);
		priv->write_reg(priv, XCAN_F_BTR_OFFSET, btr1);
	}

	netdev_dbg(ndev, "BRPR=0x%08x, BTR=0x%08x\n",
		   priv->read_reg(priv, XCAN_BRPR_OFFSET),
		   priv->read_reg(priv, XCAN_BTR_OFFSET));

	return 0;
}