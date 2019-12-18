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
struct mwifiex_adapter {int /*<<< orphan*/ * rx_workqueue; int /*<<< orphan*/ * workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_terminate_workqueue(struct mwifiex_adapter *adapter)
{
	if (adapter->workqueue) {
		flush_workqueue(adapter->workqueue);
		destroy_workqueue(adapter->workqueue);
		adapter->workqueue = NULL;
	}

	if (adapter->rx_workqueue) {
		flush_workqueue(adapter->rx_workqueue);
		destroy_workqueue(adapter->rx_workqueue);
		adapter->rx_workqueue = NULL;
	}
}