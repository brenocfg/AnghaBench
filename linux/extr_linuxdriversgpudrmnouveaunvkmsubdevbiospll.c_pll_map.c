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
struct pll_mapping {int dummy; } ;
struct nvkm_device {int card_type; int chipset; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_bios {TYPE_1__ subdev; } ;

/* Variables and functions */
#define  NV_04 134 
#define  NV_10 133 
#define  NV_11 132 
#define  NV_20 131 
#define  NV_30 130 
#define  NV_40 129 
#define  NV_50 128 
 struct pll_mapping* g84_pll_mapping ; 
 struct pll_mapping* nv04_pll_mapping ; 
 struct pll_mapping* nv40_pll_mapping ; 
 struct pll_mapping* nv50_pll_mapping ; 

__attribute__((used)) static struct pll_mapping *
pll_map(struct nvkm_bios *bios)
{
	struct nvkm_device *device = bios->subdev.device;
	switch (device->card_type) {
	case NV_04:
	case NV_10:
	case NV_11:
	case NV_20:
	case NV_30:
		return nv04_pll_mapping;
		break;
	case NV_40:
		return nv40_pll_mapping;
	case NV_50:
		if (device->chipset == 0x50)
			return nv50_pll_mapping;
		else
		if (device->chipset <  0xa3 ||
		    device->chipset == 0xaa ||
		    device->chipset == 0xac)
			return g84_pll_mapping;
	default:
		return NULL;
	}
}