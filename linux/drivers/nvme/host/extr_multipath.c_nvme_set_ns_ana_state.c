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
struct nvme_ns {scalar_t__ ana_grpid; } ;
struct nvme_ctrl {int dummy; } ;
struct nvme_ana_group_desc {int /*<<< orphan*/  grpid; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_update_ns_ana_state (struct nvme_ana_group_desc*,struct nvme_ns*) ; 

__attribute__((used)) static int nvme_set_ns_ana_state(struct nvme_ctrl *ctrl,
		struct nvme_ana_group_desc *desc, void *data)
{
	struct nvme_ns *ns = data;

	if (ns->ana_grpid == le32_to_cpu(desc->grpid)) {
		nvme_update_ns_ana_state(desc, ns);
		return -ENXIO; /* just break out of the loop */
	}

	return 0;
}