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
typedef  void* u32 ;
struct nvkm_bios {void* imaged_addr; } ;
struct nvbios_image {scalar_t__ last; scalar_t__ size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_image*,int,int) ; 
 int /*<<< orphan*/  nvbios_imagen (struct nvkm_bios*,struct nvbios_image*) ; 

bool
nvbios_image(struct nvkm_bios *bios, int idx, struct nvbios_image *image)
{
	u32 imaged_addr = bios->imaged_addr;
	memset(image, 0x00, sizeof(*image));
	bios->imaged_addr = 0;
	do {
		image->base += image->size;
		if (image->last || !nvbios_imagen(bios, image)) {
			bios->imaged_addr = imaged_addr;
			return false;
		}
	} while(idx--);
	bios->imaged_addr = imaged_addr;
	return true;
}