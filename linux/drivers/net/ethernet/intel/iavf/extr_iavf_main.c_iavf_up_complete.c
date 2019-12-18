#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct iavf_adapter {int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  aq_required; TYPE_1__ vsi; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ENABLED (struct iavf_adapter*) ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_ENABLE_QUEUES ; 
 int /*<<< orphan*/  IAVF_FLAG_CLIENT_NEEDS_OPEN ; 
 int /*<<< orphan*/  __IAVF_RUNNING ; 
 int /*<<< orphan*/  __IAVF_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_napi_enable_all (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_wq ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iavf_up_complete(struct iavf_adapter *adapter)
{
	adapter->state = __IAVF_RUNNING;
	clear_bit(__IAVF_VSI_DOWN, adapter->vsi.state);

	iavf_napi_enable_all(adapter);

	adapter->aq_required |= IAVF_FLAG_AQ_ENABLE_QUEUES;
	if (CLIENT_ENABLED(adapter))
		adapter->flags |= IAVF_FLAG_CLIENT_NEEDS_OPEN;
	mod_delayed_work(iavf_wq, &adapter->watchdog_task, 0);
}