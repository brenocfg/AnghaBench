#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {TYPE_2__* head; } ;
struct nvme_ctrl {int instance; TYPE_1__* subsys; } ;
struct TYPE_4__ {int instance; scalar_t__ disk; } ;
struct TYPE_3__ {int instance; } ;

/* Variables and functions */
 int GENHD_FL_HIDDEN ; 
 int /*<<< orphan*/  multipath ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 

void nvme_set_disk_name(char *disk_name, struct nvme_ns *ns,
			struct nvme_ctrl *ctrl, int *flags)
{
	if (!multipath) {
		sprintf(disk_name, "nvme%dn%d", ctrl->instance, ns->head->instance);
	} else if (ns->head->disk) {
		sprintf(disk_name, "nvme%dc%dn%d", ctrl->subsys->instance,
				ctrl->instance, ns->head->instance);
		*flags = GENHD_FL_HIDDEN;
	} else {
		sprintf(disk_name, "nvme%dn%d", ctrl->subsys->instance,
				ns->head->instance);
	}
}