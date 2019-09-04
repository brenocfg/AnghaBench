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
struct i40evf_adapter {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  aq_required; TYPE_1__ vsi; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ENABLED (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  I40EVF_FLAG_AQ_ENABLE_QUEUES ; 
 int /*<<< orphan*/  I40EVF_FLAG_CLIENT_NEEDS_OPEN ; 
 int /*<<< orphan*/  __I40EVF_RUNNING ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_napi_enable_all (struct i40evf_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer_pending (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void i40evf_up_complete(struct i40evf_adapter *adapter)
{
	adapter->state = __I40EVF_RUNNING;
	clear_bit(__I40E_VSI_DOWN, adapter->vsi.state);

	i40evf_napi_enable_all(adapter);

	adapter->aq_required |= I40EVF_FLAG_AQ_ENABLE_QUEUES;
	if (CLIENT_ENABLED(adapter))
		adapter->flags |= I40EVF_FLAG_CLIENT_NEEDS_OPEN;
	mod_timer_pending(&adapter->watchdog_timer, jiffies + 1);
}