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
struct iavf_adapter {int flags; int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int IAVF_FLAG_RESET_NEEDED ; 
 int IAVF_FLAG_RESET_PENDING ; 
 int /*<<< orphan*/  iavf_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iavf_schedule_reset(struct iavf_adapter *adapter)
{
	if (!(adapter->flags &
	      (IAVF_FLAG_RESET_PENDING | IAVF_FLAG_RESET_NEEDED))) {
		adapter->flags |= IAVF_FLAG_RESET_NEEDED;
		queue_work(iavf_wq, &adapter->reset_task);
	}
}