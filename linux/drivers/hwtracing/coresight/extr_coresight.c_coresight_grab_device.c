#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {scalar_t__ type; TYPE_3__ dev; TYPE_2__* pdata; } ;
struct TYPE_5__ {int nr_outport; TYPE_1__* conns; } ;
struct TYPE_4__ {struct coresight_device* child_dev; } ;

/* Variables and functions */
 scalar_t__ CORESIGHT_DEV_TYPE_HELPER ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coresight_grab_device(struct coresight_device *csdev)
{
	int i;

	for (i = 0; i < csdev->pdata->nr_outport; i++) {
		struct coresight_device *child;

		child  = csdev->pdata->conns[i].child_dev;
		if (child && child->type == CORESIGHT_DEV_TYPE_HELPER)
			pm_runtime_get_sync(child->dev.parent);
	}
	pm_runtime_get_sync(csdev->dev.parent);
}