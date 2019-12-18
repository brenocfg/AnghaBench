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
typedef  int u8 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct nvkm_bios {struct nvkm_subdev subdev; } ;
struct nvbios_M0203E {int type; } ;

/* Variables and functions */
#define  M0203E_TYPE_DDR2 134 
#define  M0203E_TYPE_DDR3 133 
#define  M0203E_TYPE_GDDR3 132 
#define  M0203E_TYPE_GDDR5 131 
#define  M0203E_TYPE_GDDR5X 130 
#define  M0203E_TYPE_GDDR6 129 
#define  M0203E_TYPE_HBM2 128 
 int NVKM_RAM_TYPE_DDR2 ; 
 int NVKM_RAM_TYPE_DDR3 ; 
 int NVKM_RAM_TYPE_GDDR3 ; 
 int NVKM_RAM_TYPE_GDDR5 ; 
 int NVKM_RAM_TYPE_GDDR5X ; 
 int NVKM_RAM_TYPE_GDDR6 ; 
 int NVKM_RAM_TYPE_HBM2 ; 
 int NVKM_RAM_TYPE_UNKNOWN ; 
 scalar_t__ nvbios_M0203Em (struct nvkm_bios*,int const,int*,int*,struct nvbios_M0203E*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,...) ; 

int
nvkm_fb_bios_memtype(struct nvkm_bios *bios)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	struct nvkm_device *device = subdev->device;
	const u8 ramcfg = (nvkm_rd32(device, 0x101000) & 0x0000003c) >> 2;
	struct nvbios_M0203E M0203E;
	u8 ver, hdr;

	if (nvbios_M0203Em(bios, ramcfg, &ver, &hdr, &M0203E)) {
		switch (M0203E.type) {
		case M0203E_TYPE_DDR2  : return NVKM_RAM_TYPE_DDR2;
		case M0203E_TYPE_DDR3  : return NVKM_RAM_TYPE_DDR3;
		case M0203E_TYPE_GDDR3 : return NVKM_RAM_TYPE_GDDR3;
		case M0203E_TYPE_GDDR5 : return NVKM_RAM_TYPE_GDDR5;
		case M0203E_TYPE_GDDR5X: return NVKM_RAM_TYPE_GDDR5X;
		case M0203E_TYPE_GDDR6 : return NVKM_RAM_TYPE_GDDR6;
		case M0203E_TYPE_HBM2  : return NVKM_RAM_TYPE_HBM2;
		default:
			nvkm_warn(subdev, "M0203E type %02x\n", M0203E.type);
			return NVKM_RAM_TYPE_UNKNOWN;
		}
	}

	nvkm_warn(subdev, "M0203E not matched!\n");
	return NVKM_RAM_TYPE_UNKNOWN;
}