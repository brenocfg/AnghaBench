#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvmet_ana_group {size_t grpid; TYPE_1__* port; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum nvme_ana_state { ____Placeholder_nvme_ana_state } nvme_ana_state ;
struct TYPE_5__ {int state; char* name; } ;
struct TYPE_4__ {int* ana_state; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* nvmet_ana_state_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct nvmet_ana_group* to_ana_group (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ana_group_ana_state_show(struct config_item *item,
		char *page)
{
	struct nvmet_ana_group *grp = to_ana_group(item);
	enum nvme_ana_state state = grp->port->ana_state[grp->grpid];
	int i;

	for (i = 0; i < ARRAY_SIZE(nvmet_ana_state_names); i++) {
		if (state != nvmet_ana_state_names[i].state)
			continue;
		return sprintf(page, "%s\n", nvmet_ana_state_names[i].name);
	}

	return sprintf(page, "\n");
}