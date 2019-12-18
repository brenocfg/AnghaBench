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
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  pmf; } ;
struct bnx2x {int flags; int /*<<< orphan*/  func_obj; TYPE_3__* pdev; TYPE_2__* msix_table; TYPE_1__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_TX_START ; 
 int /*<<< orphan*/  BNX2X_F_CMD_TX_STOP ; 
 scalar_t__ BNX2X_F_STATE_STARTED ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int USING_MSIX_FLAG ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bnx2x_func_get_state (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int /*<<< orphan*/  bnx2x_iov_wq ; 
 int /*<<< orphan*/  bnx2x_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_func_wait_started(struct bnx2x *bp)
{
	int tout = 50;
	int msix = (bp->flags & USING_MSIX_FLAG) ? 1 : 0;

	if (!bp->port.pmf)
		return 0;

	/*
	 * (assumption: No Attention from MCP at this stage)
	 * PMF probably in the middle of TX disable/enable transaction
	 * 1. Sync IRS for default SB
	 * 2. Sync SP queue - this guarantees us that attention handling started
	 * 3. Wait, that TX disable/enable transaction completes
	 *
	 * 1+2 guarantee that if DCBx attention was scheduled it already changed
	 * pending bit of transaction from STARTED-->TX_STOPPED, if we already
	 * received completion for the transaction the state is TX_STOPPED.
	 * State will return to STARTED after completion of TX_STOPPED-->STARTED
	 * transaction.
	 */

	/* make sure default SB ISR is done */
	if (msix)
		synchronize_irq(bp->msix_table[0].vector);
	else
		synchronize_irq(bp->pdev->irq);

	flush_workqueue(bnx2x_wq);
	flush_workqueue(bnx2x_iov_wq);

	while (bnx2x_func_get_state(bp, &bp->func_obj) !=
				BNX2X_F_STATE_STARTED && tout--)
		msleep(20);

	if (bnx2x_func_get_state(bp, &bp->func_obj) !=
						BNX2X_F_STATE_STARTED) {
#ifdef BNX2X_STOP_ON_ERROR
		BNX2X_ERR("Wrong function state\n");
		return -EBUSY;
#else
		/*
		 * Failed to complete the transaction in a "good way"
		 * Force both transactions with CLR bit
		 */
		struct bnx2x_func_state_params func_params = {NULL};

		DP(NETIF_MSG_IFDOWN,
		   "Hmmm... Unexpected function state! Forcing STARTED-->TX_STOPPED-->STARTED\n");

		func_params.f_obj = &bp->func_obj;
		__set_bit(RAMROD_DRV_CLR_ONLY,
					&func_params.ramrod_flags);

		/* STARTED-->TX_ST0PPED */
		func_params.cmd = BNX2X_F_CMD_TX_STOP;
		bnx2x_func_state_change(bp, &func_params);

		/* TX_ST0PPED-->STARTED */
		func_params.cmd = BNX2X_F_CMD_TX_START;
		return bnx2x_func_state_change(bp, &func_params);
#endif
	}

	return 0;
}