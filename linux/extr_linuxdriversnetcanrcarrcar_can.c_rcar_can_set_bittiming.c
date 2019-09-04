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
struct can_bittiming {scalar_t__ phase_seg2; scalar_t__ sjw; scalar_t__ brp; scalar_t__ prop_seg; scalar_t__ phase_seg1; } ;
struct TYPE_4__ {struct can_bittiming bittiming; } ;
struct rcar_can_priv {int clock_select; TYPE_1__* regs; TYPE_2__ can; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcr; } ;

/* Variables and functions */
 int RCAR_CAN_BCR_BPR (scalar_t__) ; 
 int RCAR_CAN_BCR_SJW (scalar_t__) ; 
 int RCAR_CAN_BCR_TSEG1 (scalar_t__) ; 
 int RCAR_CAN_BCR_TSEG2 (scalar_t__) ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_can_set_bittiming(struct net_device *dev)
{
	struct rcar_can_priv *priv = netdev_priv(dev);
	struct can_bittiming *bt = &priv->can.bittiming;
	u32 bcr;

	bcr = RCAR_CAN_BCR_TSEG1(bt->phase_seg1 + bt->prop_seg - 1) |
	      RCAR_CAN_BCR_BPR(bt->brp - 1) | RCAR_CAN_BCR_SJW(bt->sjw - 1) |
	      RCAR_CAN_BCR_TSEG2(bt->phase_seg2 - 1);
	/* Don't overwrite CLKR with 32-bit BCR access; CLKR has 8-bit access.
	 * All the registers are big-endian but they get byte-swapped on 32-bit
	 * read/write (but not on 8-bit, contrary to the manuals)...
	 */
	writel((bcr << 8) | priv->clock_select, &priv->regs->bcr);
}