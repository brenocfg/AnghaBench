#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct nvkm_xtensa {int addr; TYPE_2__* func; int /*<<< orphan*/  gpu_fw; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int unkd28; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int nvkm_memory_size (int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,char*) ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 
 struct nvkm_xtensa* nvkm_xtensa (struct nvkm_engine*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
nvkm_xtensa_init(struct nvkm_engine *engine)
{
	struct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	struct nvkm_subdev *subdev = &xtensa->engine.subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = xtensa->addr;
	const struct firmware *fw;
	char name[32];
	int i, ret;
	u64 addr, size;
	u32 tmp;

	if (!xtensa->gpu_fw) {
		snprintf(name, sizeof(name), "nouveau/nv84_xuc%03x",
			 xtensa->addr >> 12);

		ret = request_firmware(&fw, name, device->dev);
		if (ret) {
			nvkm_warn(subdev, "unable to load firmware %s\n", name);
			return ret;
		}

		if (fw->size > 0x40000) {
			nvkm_warn(subdev, "firmware %s too large\n", name);
			release_firmware(fw);
			return -EINVAL;
		}

		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
				      0x40000, 0x1000, false,
				      &xtensa->gpu_fw);
		if (ret) {
			release_firmware(fw);
			return ret;
		}

		nvkm_kmap(xtensa->gpu_fw);
		for (i = 0; i < fw->size / 4; i++)
			nvkm_wo32(xtensa->gpu_fw, i * 4, *((u32 *)fw->data + i));
		nvkm_done(xtensa->gpu_fw);
		release_firmware(fw);
	}

	addr = nvkm_memory_addr(xtensa->gpu_fw);
	size = nvkm_memory_size(xtensa->gpu_fw);

	nvkm_wr32(device, base + 0xd10, 0x1fffffff); /* ?? */
	nvkm_wr32(device, base + 0xd08, 0x0fffffff); /* ?? */

	nvkm_wr32(device, base + 0xd28, xtensa->func->unkd28); /* ?? */
	nvkm_wr32(device, base + 0xc20, 0x3f); /* INTR */
	nvkm_wr32(device, base + 0xd84, 0x3f); /* INTR_EN */

	nvkm_wr32(device, base + 0xcc0, addr >> 8); /* XT_REGION_BASE */
	nvkm_wr32(device, base + 0xcc4, 0x1c); /* XT_REGION_SETUP */
	nvkm_wr32(device, base + 0xcc8, size >> 8); /* XT_REGION_LIMIT */

	tmp = nvkm_rd32(device, 0x0);
	nvkm_wr32(device, base + 0xde0, tmp); /* SCRATCH_H2X */

	nvkm_wr32(device, base + 0xce8, 0xf); /* XT_REGION_SETUP */

	nvkm_wr32(device, base + 0xc20, 0x3f); /* INTR */
	nvkm_wr32(device, base + 0xd84, 0x3f); /* INTR_EN */
	return 0;
}