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
struct nvkm_ltc {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

void
gm107_ltc_cbc_clear(struct nvkm_ltc *ltc, u32 start, u32 limit)
{
	struct nvkm_device *device = ltc->subdev.device;
	nvkm_wr32(device, 0x17e270, start);
	nvkm_wr32(device, 0x17e274, limit);
	nvkm_mask(device, 0x17e26c, 0x00000000, 0x00000004);
}