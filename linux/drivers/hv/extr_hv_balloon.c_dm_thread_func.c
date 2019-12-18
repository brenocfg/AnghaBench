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
struct hv_dynmem_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_event; } ;

/* Variables and functions */
 int HZ ; 
 TYPE_1__ dm_device ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  post_status (struct hv_dynmem_device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dm_thread_func(void *dm_dev)
{
	struct hv_dynmem_device *dm = dm_dev;

	while (!kthread_should_stop()) {
		wait_for_completion_interruptible_timeout(
						&dm_device.config_event, 1*HZ);
		/*
		 * The host expects us to post information on the memory
		 * pressure every second.
		 */
		reinit_completion(&dm_device.config_event);
		post_status(dm);
	}

	return 0;
}