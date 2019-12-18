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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_pmu {struct nvkm_subdev subdev; } ;
struct nvkm_memx {int /*<<< orphan*/  base; struct nvkm_pmu* pmu; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMX_MSG_EXEC ; 
 int /*<<< orphan*/  PROC_MEMX ; 
 int /*<<< orphan*/  kfree (struct nvkm_memx*) ; 
 int /*<<< orphan*/  memx_out (struct nvkm_memx*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  nvkm_pmu_send (struct nvkm_pmu*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

int
nvkm_memx_fini(struct nvkm_memx **pmemx, bool exec)
{
	struct nvkm_memx *memx = *pmemx;
	struct nvkm_pmu *pmu = memx->pmu;
	struct nvkm_subdev *subdev = &pmu->subdev;
	struct nvkm_device *device = subdev->device;
	u32 finish, reply[2];

	/* flush the cache... */
	memx_out(memx);

	/* release data segment access */
	finish = nvkm_rd32(device, 0x10a1c0) & 0x00ffffff;
	nvkm_wr32(device, 0x10a580, 0x00000000);

	/* call MEMX process to execute the script, and wait for reply */
	if (exec) {
		nvkm_pmu_send(pmu, reply, PROC_MEMX, MEMX_MSG_EXEC,
			      memx->base, finish);
		nvkm_debug(subdev, "Exec took %uns, PMU_IN %08x\n",
			   reply[0], reply[1]);
	}

	kfree(memx);
	return 0;
}