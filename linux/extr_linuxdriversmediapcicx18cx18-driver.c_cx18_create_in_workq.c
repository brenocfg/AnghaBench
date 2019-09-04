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
struct TYPE_2__ {char* name; } ;
struct cx18 {int /*<<< orphan*/  in_work_queue; int /*<<< orphan*/  in_workq_name; TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int cx18_create_in_workq(struct cx18 *cx)
{
	snprintf(cx->in_workq_name, sizeof(cx->in_workq_name), "%s-in",
		 cx->v4l2_dev.name);
	cx->in_work_queue = alloc_ordered_workqueue("%s", 0, cx->in_workq_name);
	if (!cx->in_work_queue) {
		CX18_ERR("Unable to create incoming mailbox handler thread\n");
		return -ENOMEM;
	}
	return 0;
}