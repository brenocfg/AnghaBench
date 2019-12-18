#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_ram {TYPE_1__* fb; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_16__ {int* data; } ;
struct TYPE_15__ {int* data; } ;
struct TYPE_14__ {int* data; } ;
struct TYPE_13__ {int* data; } ;
struct TYPE_12__ {int* data; } ;
struct TYPE_11__ {int* data; } ;
struct TYPE_10__ {int* data; } ;
struct gk104_ram_train {int mask; TYPE_8__ type04; TYPE_7__ type01; TYPE_6__ type07; TYPE_5__ type09; TYPE_4__ type00; TYPE_3__ type06; TYPE_2__ type08; } ;
struct TYPE_9__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
gk104_ram_train_init_0(struct nvkm_ram *ram, struct gk104_ram_train *train)
{
	struct nvkm_subdev *subdev = &ram->fb->subdev;
	struct nvkm_device *device = subdev->device;
	int i, j;

	if ((train->mask & 0x03d3) != 0x03d3) {
		nvkm_warn(subdev, "missing link training data\n");
		return -EINVAL;
	}

	for (i = 0; i < 0x30; i++) {
		for (j = 0; j < 8; j += 4) {
			nvkm_wr32(device, 0x10f968 + j, 0x00000000 | (i << 8));
			nvkm_wr32(device, 0x10f920 + j, 0x00000000 |
						   train->type08.data[i] << 4 |
						   train->type06.data[i]);
			nvkm_wr32(device, 0x10f918 + j, train->type00.data[i]);
			nvkm_wr32(device, 0x10f920 + j, 0x00000100 |
						   train->type09.data[i] << 4 |
						   train->type07.data[i]);
			nvkm_wr32(device, 0x10f918 + j, train->type01.data[i]);
		}
	}

	for (j = 0; j < 8; j += 4) {
		for (i = 0; i < 0x100; i++) {
			nvkm_wr32(device, 0x10f968 + j, i);
			nvkm_wr32(device, 0x10f900 + j, train->type04.data[i]);
		}
	}

	return 0;
}