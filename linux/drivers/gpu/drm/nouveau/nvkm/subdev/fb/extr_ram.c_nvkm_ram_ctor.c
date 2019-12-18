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
typedef  int u64 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_ram_func {int dummy; } ;
struct nvkm_ram {int type; int size; int /*<<< orphan*/  vram; struct nvkm_fb* fb; struct nvkm_ram_func const* func; } ;
struct nvkm_fb {struct nvkm_subdev subdev; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_RAM_MM_NORMAL ; 
 int NVKM_RAM_MM_SHIFT ; 
#define  NVKM_RAM_TYPE_DDR1 141 
#define  NVKM_RAM_TYPE_DDR2 140 
#define  NVKM_RAM_TYPE_DDR3 139 
#define  NVKM_RAM_TYPE_GDDR2 138 
#define  NVKM_RAM_TYPE_GDDR3 137 
#define  NVKM_RAM_TYPE_GDDR4 136 
#define  NVKM_RAM_TYPE_GDDR5 135 
#define  NVKM_RAM_TYPE_GDDR5X 134 
#define  NVKM_RAM_TYPE_GDDR6 133 
#define  NVKM_RAM_TYPE_HBM2 132 
#define  NVKM_RAM_TYPE_SDRAM 131 
#define  NVKM_RAM_TYPE_SGRAM 130 
#define  NVKM_RAM_TYPE_STOLEN 129 
#define  NVKM_RAM_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  nvkm_info (struct nvkm_subdev*,char*,int,char const*) ; 
 int nvkm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_mm_initialised (int /*<<< orphan*/ *) ; 

int
nvkm_ram_ctor(const struct nvkm_ram_func *func, struct nvkm_fb *fb,
	      enum nvkm_ram_type type, u64 size, struct nvkm_ram *ram)
{
	static const char *name[] = {
		[NVKM_RAM_TYPE_UNKNOWN] = "of unknown memory type",
		[NVKM_RAM_TYPE_STOLEN ] = "stolen system memory",
		[NVKM_RAM_TYPE_SGRAM  ] = "SGRAM",
		[NVKM_RAM_TYPE_SDRAM  ] = "SDRAM",
		[NVKM_RAM_TYPE_DDR1   ] = "DDR1",
		[NVKM_RAM_TYPE_DDR2   ] = "DDR2",
		[NVKM_RAM_TYPE_DDR3   ] = "DDR3",
		[NVKM_RAM_TYPE_GDDR2  ] = "GDDR2",
		[NVKM_RAM_TYPE_GDDR3  ] = "GDDR3",
		[NVKM_RAM_TYPE_GDDR4  ] = "GDDR4",
		[NVKM_RAM_TYPE_GDDR5  ] = "GDDR5",
		[NVKM_RAM_TYPE_GDDR5X ] = "GDDR5X",
		[NVKM_RAM_TYPE_GDDR6  ] = "GDDR6",
		[NVKM_RAM_TYPE_HBM2   ] = "HBM2",
	};
	struct nvkm_subdev *subdev = &fb->subdev;
	int ret;

	nvkm_info(subdev, "%d MiB %s\n", (int)(size >> 20), name[type]);
	ram->func = func;
	ram->fb = fb;
	ram->type = type;
	ram->size = size;

	if (!nvkm_mm_initialised(&ram->vram)) {
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL, 0,
				   size >> NVKM_RAM_MM_SHIFT, 1);
		if (ret)
			return ret;
	}

	return 0;
}