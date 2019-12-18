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
struct gfar_extra_stats {int /*<<< orphan*/  rx_alloc_err; } ;
struct gfar_private {struct gfar_extra_stats extra_stats; } ;
struct gfar_priv_rx_q {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct gfar_private* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfar_rx_alloc_err(struct gfar_priv_rx_q *rx_queue)
{
	struct gfar_private *priv = netdev_priv(rx_queue->ndev);
	struct gfar_extra_stats *estats = &priv->extra_stats;

	netdev_err(rx_queue->ndev, "Can't alloc RX buffers\n");
	atomic64_inc(&estats->rx_alloc_err);
}