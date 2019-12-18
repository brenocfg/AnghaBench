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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_falcon {scalar_t__ addr; TYPE_1__* owner; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;

/* Variables and functions */
 int nvkm_wait_msec (struct nvkm_device*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
nvkm_falcon_v1_wait_for_halt(struct nvkm_falcon *falcon, u32 ms)
{
	struct nvkm_device *device = falcon->owner->device;
	int ret;

	ret = nvkm_wait_msec(device, ms, falcon->addr + 0x100, 0x10, 0x10);
	if (ret < 0)
		return ret;

	return 0;
}