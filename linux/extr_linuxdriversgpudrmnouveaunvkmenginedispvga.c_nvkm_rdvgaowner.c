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
typedef  scalar_t__ u32 ;
struct nvkm_device {scalar_t__ card_type; int chipset; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int nvkm_rdvgac (struct nvkm_device*,int,int) ; 

u8
nvkm_rdvgaowner(struct nvkm_device *device)
{
	if (device->card_type < NV_50) {
		if (device->chipset == 0x11) {
			u32 tied = nvkm_rd32(device, 0x001084) & 0x10000000;
			if (tied == 0) {
				u8 slA = nvkm_rdvgac(device, 0, 0x28) & 0x80;
				u8 tvA = nvkm_rdvgac(device, 0, 0x33) & 0x01;
				u8 slB = nvkm_rdvgac(device, 1, 0x28) & 0x80;
				u8 tvB = nvkm_rdvgac(device, 1, 0x33) & 0x01;
				if (slA && !tvA) return 0x00;
				if (slB && !tvB) return 0x03;
				if (slA) return 0x00;
				if (slB) return 0x03;
				return 0x00;
			}
			return 0x04;
		}

		return nvkm_rdvgac(device, 0, 0x44);
	}

	return 0x00;
}