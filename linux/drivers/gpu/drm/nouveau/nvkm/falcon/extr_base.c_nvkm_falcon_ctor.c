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
typedef  int u32 ;
struct nvkm_subdev {int index; } ;
struct nvkm_falcon_func {int dummy; } ;
struct TYPE_4__ {int ports; int limit; } ;
struct TYPE_3__ {int ports; int limit; } ;
struct nvkm_falcon {char const* name; int addr; int version; int secret; int has_emem; int debug; TYPE_2__ data; TYPE_1__ code; int /*<<< orphan*/  dmem_mutex; int /*<<< orphan*/  mutex; struct nvkm_subdev* owner; struct nvkm_falcon_func const* func; } ;

/* Variables and functions */
#define  NVKM_ENGINE_GR 132 
#define  NVKM_ENGINE_NVDEC0 131 
#define  NVKM_ENGINE_SEC2 130 
#define  NVKM_SUBDEV_GSP 129 
#define  NVKM_SUBDEV_PMU 128 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 
 int /*<<< orphan*/ * nvkm_subdev_name ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int /*<<< orphan*/ ) ; 

void
nvkm_falcon_ctor(const struct nvkm_falcon_func *func,
		 struct nvkm_subdev *subdev, const char *name, u32 addr,
		 struct nvkm_falcon *falcon)
{
	u32 debug_reg;
	u32 reg;

	falcon->func = func;
	falcon->owner = subdev;
	falcon->name = name;
	falcon->addr = addr;
	mutex_init(&falcon->mutex);
	mutex_init(&falcon->dmem_mutex);

	reg = nvkm_falcon_rd32(falcon, 0x12c);
	falcon->version = reg & 0xf;
	falcon->secret = (reg >> 4) & 0x3;
	falcon->code.ports = (reg >> 8) & 0xf;
	falcon->data.ports = (reg >> 12) & 0xf;

	reg = nvkm_falcon_rd32(falcon, 0x108);
	falcon->code.limit = (reg & 0x1ff) << 8;
	falcon->data.limit = (reg & 0x3fe00) >> 1;

	switch (subdev->index) {
	case NVKM_ENGINE_GR:
		debug_reg = 0x0;
		break;
	case NVKM_SUBDEV_PMU:
		debug_reg = 0xc08;
		break;
	case NVKM_ENGINE_NVDEC0:
		debug_reg = 0xd00;
		break;
	case NVKM_ENGINE_SEC2:
		debug_reg = 0x408;
		falcon->has_emem = true;
		break;
	case NVKM_SUBDEV_GSP:
		debug_reg = 0x0; /*XXX*/
		break;
	default:
		nvkm_warn(subdev, "unsupported falcon %s!\n",
			  nvkm_subdev_name[subdev->index]);
		debug_reg = 0;
		break;
	}

	if (debug_reg) {
		u32 val = nvkm_falcon_rd32(falcon, debug_reg);
		falcon->debug = (val >> 20) & 0x1;
	}
}