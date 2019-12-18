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
typedef  int u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_pmu {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MEMX_INFO_TRAIN ; 
 int /*<<< orphan*/  MEMX_MSG_INFO ; 
 int /*<<< orphan*/  PROC_MEMX ; 
 int nvkm_pmu_send (struct nvkm_pmu*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

int
nvkm_memx_train_result(struct nvkm_pmu *pmu, u32 *res, int rsize)
{
	struct nvkm_device *device = pmu->subdev.device;
	u32 reply[2], base, size, i;
	int ret;

	ret = nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_INFO,
			    MEMX_INFO_TRAIN, 0);
	if (ret)
		return ret;

	base = reply[0];
	size = reply[1] >> 2;
	if (size > rsize)
		return -ENOMEM;

	/* read the packet */
	nvkm_wr32(device, 0x10a1c0, 0x02000000 | base);

	for (i = 0; i < size; i++)
		res[i] = nvkm_rd32(device, 0x10a1c4);

	return 0;
}