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
struct nvme_ns {int dummy; } ;
struct nvme_id_ns {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void nvme_mpath_add_disk(struct nvme_ns *ns,
		struct nvme_id_ns *id)
{
}