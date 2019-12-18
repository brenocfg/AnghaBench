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
struct ec_bhf_priv {size_t tx_dnext; int /*<<< orphan*/  net_dev; int /*<<< orphan*/ * tx_descs; } ;

/* Variables and functions */
 scalar_t__ ec_bhf_desc_sent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ec_bhf_process_tx(struct ec_bhf_priv *priv)
{
	if (unlikely(netif_queue_stopped(priv->net_dev))) {
		/* Make sure that we perceive changes to tx_dnext. */
		smp_rmb();

		if (ec_bhf_desc_sent(&priv->tx_descs[priv->tx_dnext]))
			netif_wake_queue(priv->net_dev);
	}
}