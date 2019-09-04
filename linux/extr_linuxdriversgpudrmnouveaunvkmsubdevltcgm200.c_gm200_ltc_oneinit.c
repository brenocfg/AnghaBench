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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_ltc {int ltc_nr; int lts_nr; TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int gf100_ltc_oneinit_tag_ram (struct nvkm_ltc*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
gm200_ltc_oneinit(struct nvkm_ltc *ltc)
{
	struct nvkm_device *device = ltc->subdev.device;

	ltc->ltc_nr = nvkm_rd32(device, 0x12006c);
	ltc->lts_nr = nvkm_rd32(device, 0x17e280) >> 28;

	return gf100_ltc_oneinit_tag_ram(ltc);
}