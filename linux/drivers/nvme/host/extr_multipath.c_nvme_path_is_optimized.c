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
struct nvme_ns {scalar_t__ ana_state; TYPE_1__* ctrl; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ NVME_ANA_OPTIMIZED ; 
 scalar_t__ NVME_CTRL_LIVE ; 

__attribute__((used)) static inline bool nvme_path_is_optimized(struct nvme_ns *ns)
{
	return ns->ctrl->state == NVME_CTRL_LIVE &&
		ns->ana_state == NVME_ANA_OPTIMIZED;
}