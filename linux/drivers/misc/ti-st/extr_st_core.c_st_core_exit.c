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
struct st_data_s {int /*<<< orphan*/  tx_skb; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_TI_WL ; 
 int /*<<< orphan*/  kfree (struct st_data_s*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 long st_ll_deinit (struct st_data_s*) ; 
 long tty_unregister_ldisc (int /*<<< orphan*/ ) ; 

void st_core_exit(struct st_data_s *st_gdata)
{
	long err;
	/* internal module cleanup */
	err = st_ll_deinit(st_gdata);
	if (err)
		pr_err("error during deinit of ST LL %ld", err);

	if (st_gdata != NULL) {
		/* Free ST Tx Qs and skbs */
		skb_queue_purge(&st_gdata->txq);
		skb_queue_purge(&st_gdata->tx_waitq);
		kfree_skb(st_gdata->rx_skb);
		kfree_skb(st_gdata->tx_skb);
		/* TTY ldisc cleanup */
		err = tty_unregister_ldisc(N_TI_WL);
		if (err)
			pr_err("unable to un-register ldisc %ld", err);
		/* free the global data pointer */
		kfree(st_gdata);
	}
}