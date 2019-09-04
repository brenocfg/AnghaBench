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
struct i40evf_adapter {int flags; int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int I40EVF_FLAG_RESET_NEEDED ; 
 int I40EVF_FLAG_RESET_PENDING ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void i40evf_schedule_reset(struct i40evf_adapter *adapter)
{
	if (!(adapter->flags &
	      (I40EVF_FLAG_RESET_PENDING | I40EVF_FLAG_RESET_NEEDED))) {
		adapter->flags |= I40EVF_FLAG_RESET_NEEDED;
		schedule_work(&adapter->reset_task);
	}
}