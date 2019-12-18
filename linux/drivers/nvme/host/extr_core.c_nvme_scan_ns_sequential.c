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
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_remove_invalid_namespaces (struct nvme_ctrl*,unsigned int) ; 
 int /*<<< orphan*/  nvme_validate_ns (struct nvme_ctrl*,unsigned int) ; 

__attribute__((used)) static void nvme_scan_ns_sequential(struct nvme_ctrl *ctrl, unsigned nn)
{
	unsigned i;

	for (i = 1; i <= nn; i++)
		nvme_validate_ns(ctrl, i);

	nvme_remove_invalid_namespaces(ctrl, nn);
}