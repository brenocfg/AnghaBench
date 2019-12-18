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
struct fjes_hw {int /*<<< orphan*/  update_zone_task; } ;
struct fjes_adapter {int /*<<< orphan*/  control_wq; struct fjes_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fjes_update_zone_irq(struct fjes_adapter *adapter,
				 int src_epid)
{
	struct fjes_hw *hw = &adapter->hw;

	if (!work_pending(&hw->update_zone_task))
		queue_work(adapter->control_wq, &hw->update_zone_task);
}