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
struct BCState {int /*<<< orphan*/  Flag; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  squeue; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  BC_FLG_INIT ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_hfcpci (struct BCState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
close_hfcpci(struct BCState *bcs)
{
	mode_hfcpci(bcs, 0, bcs->channel);
	if (test_and_clear_bit(BC_FLG_INIT, &bcs->Flag)) {
		skb_queue_purge(&bcs->rqueue);
		skb_queue_purge(&bcs->squeue);
		if (bcs->tx_skb) {
			dev_kfree_skb_any(bcs->tx_skb);
			bcs->tx_skb = NULL;
			test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
		}
	}
}