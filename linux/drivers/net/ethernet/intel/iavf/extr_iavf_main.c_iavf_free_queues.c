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
struct iavf_adapter {int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * tx_rings; scalar_t__ num_active_queues; int /*<<< orphan*/  vsi_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iavf_free_queues(struct iavf_adapter *adapter)
{
	if (!adapter->vsi_res)
		return;
	adapter->num_active_queues = 0;
	kfree(adapter->tx_rings);
	adapter->tx_rings = NULL;
	kfree(adapter->rx_rings);
	adapter->rx_rings = NULL;
}