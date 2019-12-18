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
struct nvme_ns_head {int dummy; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int nvme_mpath_alloc_disk(struct nvme_ctrl *ctrl,
		struct nvme_ns_head *head)
{
	return 0;
}