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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
gp10b_ibus_init(struct nvkm_subdev *ibus)
{
	struct nvkm_device *device = ibus->device;

	nvkm_wr32(device, 0x1200a8, 0x0);

	/* init ring */
	nvkm_wr32(device, 0x12004c, 0x4);
	nvkm_wr32(device, 0x122204, 0x2);
	nvkm_rd32(device, 0x122204);

	/* timeout configuration */
	nvkm_wr32(device, 0x009080, 0x800186a0);

	return 0;
}