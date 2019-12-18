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
struct dchannel {int /*<<< orphan*/  Flags; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  squeue; scalar_t__ tx_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_TX_BUSY ; 
 int /*<<< orphan*/  confirm_Dsend (struct dchannel*) ; 
 int /*<<< orphan*/ * skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
get_next_dframe(struct dchannel *dch)
{
	dch->tx_idx = 0;
	dch->tx_skb = skb_dequeue(&dch->squeue);
	if (dch->tx_skb) {
		confirm_Dsend(dch);
		return 1;
	}
	dch->tx_skb = NULL;
	test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
	return 0;
}