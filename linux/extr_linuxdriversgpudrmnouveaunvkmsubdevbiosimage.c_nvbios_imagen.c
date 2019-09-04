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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_bios {struct nvkm_subdev subdev; } ;
struct nvbios_pcirT {int image_type; int last; int /*<<< orphan*/  image_size; } ;
struct nvbios_npdeT {int last; int /*<<< orphan*/  image_size; } ;
struct nvbios_image {int type; int last; int /*<<< orphan*/  size; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvbios_npdeTp (struct nvkm_bios*,scalar_t__,struct nvbios_npdeT*) ; 
 int /*<<< orphan*/  nvbios_pcirTp (struct nvkm_bios*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_pcirT*) ; 
 int /*<<< orphan*/  nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nvbios_imagen(struct nvkm_bios *bios, struct nvbios_image *image)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	struct nvbios_pcirT pcir;
	struct nvbios_npdeT npde;
	u8  ver;
	u16 hdr;
	u32 data;

	switch ((data = nvbios_rd16(bios, image->base + 0x00))) {
	case 0xaa55:
	case 0xbb77:
	case 0x4e56: /* NV */
		break;
	default:
		nvkm_debug(subdev, "%08x: ROM signature (%04x) unknown\n",
			   image->base, data);
		return false;
	}

	if (!(data = nvbios_pcirTp(bios, image->base, &ver, &hdr, &pcir)))
		return false;
	image->size = pcir.image_size;
	image->type = pcir.image_type;
	image->last = pcir.last;

	if (image->type != 0x70) {
		if (!(data = nvbios_npdeTp(bios, image->base, &npde)))
			return true;
		image->size = npde.image_size;
		image->last = npde.last;
	} else {
		image->last = true;
	}

	return true;
}