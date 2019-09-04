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
struct TYPE_2__ {int /*<<< orphan*/  writes; int /*<<< orphan*/  worker; int /*<<< orphan*/  wq; } ;
struct drbd_device {TYPE_1__ submit; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_submit ; 

__attribute__((used)) static int init_submitter(struct drbd_device *device)
{
	/* opencoded create_singlethread_workqueue(),
	 * to be able to say "drbd%d", ..., minor */
	device->submit.wq =
		alloc_ordered_workqueue("drbd%u_submit", WQ_MEM_RECLAIM, device->minor);
	if (!device->submit.wq)
		return -ENOMEM;

	INIT_WORK(&device->submit.worker, do_submit);
	INIT_LIST_HEAD(&device->submit.writes);
	return 0;
}