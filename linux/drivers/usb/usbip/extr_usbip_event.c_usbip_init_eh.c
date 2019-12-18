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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WORK_QUEUE_NAME ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ * usbip_queue ; 

int usbip_init_eh(void)
{
	usbip_queue = create_singlethread_workqueue(WORK_QUEUE_NAME);
	if (usbip_queue == NULL) {
		pr_err("failed to create usbip_event\n");
		return -ENOMEM;
	}
	return 0;
}