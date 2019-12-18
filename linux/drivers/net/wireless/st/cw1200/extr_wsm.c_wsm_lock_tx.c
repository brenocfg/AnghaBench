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
struct cw1200_common {int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 
 scalar_t__ wsm_flush_tx (struct cw1200_common*) ; 

void wsm_lock_tx(struct cw1200_common *priv)
{
	wsm_cmd_lock(priv);
	if (atomic_add_return(1, &priv->tx_lock) == 1) {
		if (wsm_flush_tx(priv))
			pr_debug("[WSM] TX is locked.\n");
	}
	wsm_cmd_unlock(priv);
}