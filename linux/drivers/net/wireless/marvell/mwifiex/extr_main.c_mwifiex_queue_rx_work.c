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
struct mwifiex_adapter {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_workqueue; int /*<<< orphan*/  rx_proc_lock; scalar_t__ rx_processing; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_queue_rx_work(struct mwifiex_adapter *adapter)
{
	spin_lock_bh(&adapter->rx_proc_lock);
	if (adapter->rx_processing) {
		spin_unlock_bh(&adapter->rx_proc_lock);
	} else {
		spin_unlock_bh(&adapter->rx_proc_lock);
		queue_work(adapter->rx_workqueue, &adapter->rx_work);
	}
}