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
struct cw1200_common {int /*<<< orphan*/  bh_error; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_bh_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void wsm_unlock_tx(struct cw1200_common *priv)
{
	int tx_lock;
	tx_lock = atomic_sub_return(1, &priv->tx_lock);
	BUG_ON(tx_lock < 0);

	if (tx_lock == 0) {
		if (!priv->bh_error)
			cw1200_bh_wakeup(priv);
		pr_debug("[WSM] TX is unlocked.\n");
	}
}