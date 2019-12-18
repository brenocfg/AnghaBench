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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_mc {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gf100_mc_intr_mask(struct nvkm_mc *mc, u32 mask, u32 stat)
{
	struct nvkm_device *device = mc->subdev.device;
	nvkm_mask(device, 0x000640, mask, stat);
	nvkm_mask(device, 0x000644, mask, stat);
}