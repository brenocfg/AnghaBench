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
struct xenvif {int disabled; int /*<<< orphan*/ * queues; scalar_t__ num_queues; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xenvif_kick_thread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xenvif_fatal_tx_err(struct xenvif *vif)
{
	netdev_err(vif->dev, "fatal error; disabling device\n");
	vif->disabled = true;
	/* Disable the vif from queue 0's kthread */
	if (vif->num_queues)
		xenvif_kick_thread(&vif->queues[0]);
}