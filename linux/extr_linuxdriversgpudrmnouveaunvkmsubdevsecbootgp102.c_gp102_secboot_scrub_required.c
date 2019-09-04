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
struct nvkm_secboot {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static bool
gp102_secboot_scrub_required(struct nvkm_secboot *sb)
{
	struct nvkm_subdev *subdev = &sb->subdev;
	struct nvkm_device *device = subdev->device;
	u32 reg;

	nvkm_wr32(device, 0x100cd0, 0x2);
	reg = nvkm_rd32(device, 0x100cd0);

	return (reg & BIT(4));
}