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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct nvkm_secboot {TYPE_2__ subdev; } ;
struct nvkm_pmu {TYPE_3__* falcon; int /*<<< orphan*/  queue; } ;
struct nvkm_device {struct nvkm_pmu* pmu; } ;
struct nvkm_acr {size_t boot_falcon; } ;
struct TYPE_4__ {scalar_t__ limit; } ;
struct TYPE_6__ {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ NVKM_MSGQUEUE_CMDLINE_SIZE ; 
 int acr_ls_msgqueue_post_run (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_debug (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvkm_secboot_falcon_name ; 

int
acr_ls_pmu_post_run(const struct nvkm_acr *acr, const struct nvkm_secboot *sb)
{
	struct nvkm_device *device = sb->subdev.device;
	struct nvkm_pmu *pmu = device->pmu;
	u32 addr_args = pmu->falcon->data.limit - NVKM_MSGQUEUE_CMDLINE_SIZE;
	int ret;

	ret = acr_ls_msgqueue_post_run(pmu->queue, pmu->falcon, addr_args);
	if (ret)
		return ret;

	nvkm_debug(&sb->subdev, "%s started\n",
		   nvkm_secboot_falcon_name[acr->boot_falcon]);

	return 0;
}