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
struct st_data_s {int /*<<< orphan*/  work_write_wakeup; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_TI_WL ; 
 int /*<<< orphan*/  kfree (struct st_data_s*) ; 
 struct st_data_s* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_ldisc_ops ; 
 long st_ll_init (struct st_data_s*) ; 
 long tty_register_ldisc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long tty_unregister_ldisc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_fn_write_wakeup ; 

int st_core_init(struct st_data_s **core_data)
{
	struct st_data_s *st_gdata;
	long err;

	err = tty_register_ldisc(N_TI_WL, &st_ldisc_ops);
	if (err) {
		pr_err("error registering %d line discipline %ld",
			   N_TI_WL, err);
		return err;
	}
	pr_debug("registered n_shared line discipline");

	st_gdata = kzalloc(sizeof(struct st_data_s), GFP_KERNEL);
	if (!st_gdata) {
		pr_err("memory allocation failed");
		err = tty_unregister_ldisc(N_TI_WL);
		if (err)
			pr_err("unable to un-register ldisc %ld", err);
		err = -ENOMEM;
		return err;
	}

	/* Initialize ST TxQ and Tx waitQ queue head. All BT/FM/GPS module skb's
	 * will be pushed in this queue for actual transmission.
	 */
	skb_queue_head_init(&st_gdata->txq);
	skb_queue_head_init(&st_gdata->tx_waitq);

	/* Locking used in st_int_enqueue() to avoid multiple execution */
	spin_lock_init(&st_gdata->lock);

	err = st_ll_init(st_gdata);
	if (err) {
		pr_err("error during st_ll initialization(%ld)", err);
		kfree(st_gdata);
		err = tty_unregister_ldisc(N_TI_WL);
		if (err)
			pr_err("unable to un-register ldisc");
		return err;
	}

	INIT_WORK(&st_gdata->work_write_wakeup, work_fn_write_wakeup);

	*core_data = st_gdata;
	return 0;
}