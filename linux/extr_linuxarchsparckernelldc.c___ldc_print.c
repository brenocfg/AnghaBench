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
struct ldc_channel {int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  tx_num_entries; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  rx_num_entries; int /*<<< orphan*/  rx_tail; int /*<<< orphan*/  rx_head; int /*<<< orphan*/  hs_state; int /*<<< orphan*/  chan_state; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_str (int /*<<< orphan*/ ) ; 

void __ldc_print(struct ldc_channel *lp, const char *caller)
{
	pr_info("%s: id=0x%lx flags=0x%x state=%s cstate=0x%lx hsstate=0x%x\n"
		"\trx_h=0x%lx rx_t=0x%lx rx_n=%ld\n"
		"\ttx_h=0x%lx tx_t=0x%lx tx_n=%ld\n"
		"\trcv_nxt=%u snd_nxt=%u\n",
		caller, lp->id, lp->flags, state_to_str(lp->state),
		lp->chan_state, lp->hs_state,
		lp->rx_head, lp->rx_tail, lp->rx_num_entries,
		lp->tx_head, lp->tx_tail, lp->tx_num_entries,
		lp->rcv_nxt, lp->snd_nxt);
}