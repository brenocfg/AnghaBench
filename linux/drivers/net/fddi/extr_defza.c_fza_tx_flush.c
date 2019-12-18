#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct fza_private {int ring_smt_tx_index; int ring_smt_tx_size; int ring_rmc_tx_index; int ring_rmc_tx_size; TYPE_3__* regs; TYPE_2__* ring_rmc_tx; TYPE_1__* ring_smt_tx; } ;
struct TYPE_6__ {int /*<<< orphan*/  control_a; } ;
struct TYPE_5__ {int /*<<< orphan*/  rmc; int /*<<< orphan*/  own; } ;
struct TYPE_4__ {int /*<<< orphan*/  own; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZA_CONTROL_A_FLUSH_DONE ; 
 int /*<<< orphan*/  FZA_RING_OWN_FZA ; 
 int FZA_RING_OWN_MASK ; 
 int FZA_RING_TX_DTP ; 
 int FZA_RING_TX_OWN_RMC ; 
 struct fza_private* netdev_priv (struct net_device*) ; 
 int readl_o (int /*<<< orphan*/ *) ; 
 int readl_u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_u (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fza_tx_flush(struct net_device *dev)
{
	struct fza_private *fp = netdev_priv(dev);
	u32 own;
	int i;

	/* Clean up the SMT TX ring. */
	i = fp->ring_smt_tx_index;
	do {
		writel_o(FZA_RING_OWN_FZA, &fp->ring_smt_tx[i].own);
		fp->ring_smt_tx_index =
			(fp->ring_smt_tx_index + 1) % fp->ring_smt_tx_size;

	} while (i != fp->ring_smt_tx_index);

	/* Clean up the RMC TX ring. */
	i = fp->ring_rmc_tx_index;
	do {
		own = readl_o(&fp->ring_rmc_tx[i].own);
		if ((own & FZA_RING_OWN_MASK) == FZA_RING_TX_OWN_RMC) {
			u32 rmc = readl_u(&fp->ring_rmc_tx[i].rmc);

			writel_u(rmc | FZA_RING_TX_DTP,
				 &fp->ring_rmc_tx[i].rmc);
		}
		fp->ring_rmc_tx_index =
			(fp->ring_rmc_tx_index + 1) % fp->ring_rmc_tx_size;

	} while (i != fp->ring_rmc_tx_index);

	/* Done. */
	writew_o(FZA_CONTROL_A_FLUSH_DONE, &fp->regs->control_a);
}