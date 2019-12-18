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
struct nvkm_falcon {int /*<<< orphan*/  user; scalar_t__ addr; TYPE_1__* owner; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;

/* Variables and functions */
 int falcon_v1_wait_idle (struct nvkm_falcon*) ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 
 int nvkm_wait_msec (struct nvkm_device*,int,scalar_t__,int,int) ; 

__attribute__((used)) static int
nvkm_falcon_v1_enable(struct nvkm_falcon *falcon)
{
	struct nvkm_device *device = falcon->owner->device;
	int ret;

	ret = nvkm_wait_msec(device, 10, falcon->addr + 0x10c, 0x6, 0x0);
	if (ret < 0) {
		nvkm_error(falcon->user, "Falcon mem scrubbing timeout\n");
		return ret;
	}

	ret = falcon_v1_wait_idle(falcon);
	if (ret)
		return ret;

	/* enable IRQs */
	nvkm_falcon_wr32(falcon, 0x010, 0xff);

	return 0;
}