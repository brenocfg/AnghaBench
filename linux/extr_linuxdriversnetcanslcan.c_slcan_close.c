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
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;
struct slcan {scalar_t__ magic; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  lock; struct tty_struct* tty; } ;

/* Variables and functions */
 scalar_t__ SLCAN_MAGIC ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slcan_close(struct tty_struct *tty)
{
	struct slcan *sl = (struct slcan *) tty->disc_data;

	/* First make sure we're connected. */
	if (!sl || sl->magic != SLCAN_MAGIC || sl->tty != tty)
		return;

	spin_lock_bh(&sl->lock);
	tty->disc_data = NULL;
	sl->tty = NULL;
	spin_unlock_bh(&sl->lock);

	flush_work(&sl->tx_work);

	/* Flush network side */
	unregister_netdev(sl->dev);
	/* This will complete via sl_free_netdev */
}