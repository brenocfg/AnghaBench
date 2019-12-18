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
typedef  int u32 ;
struct shadow {TYPE_1__* func; int /*<<< orphan*/  data; } ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_bios {int /*<<< orphan*/ * data; struct nvkm_subdev subdev; } ;
struct nvbios_image {int base; int type; int size; int last; } ;
struct TYPE_2__ {int (* size ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  rw; int /*<<< orphan*/  require_checksum; int /*<<< orphan*/  ignore_checksum; scalar_t__ no_pcir; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvbios_checksum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvbios_image (struct nvkm_bios*,int,struct nvbios_image*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int /*<<< orphan*/  shadow_fetch (struct nvkm_bios*,struct shadow*,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shadow_image(struct nvkm_bios *bios, int idx, u32 offset, struct shadow *mthd)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	struct nvbios_image image;
	int score = 1;

	if (mthd->func->no_pcir) {
		image.base = 0;
		image.type = 0;
		image.size = mthd->func->size(mthd->data);
		image.last = 1;
	} else {
		if (!shadow_fetch(bios, mthd, offset + 0x1000)) {
			nvkm_debug(subdev, "%08x: header fetch failed\n",
				   offset);
			return 0;
		}

		if (!nvbios_image(bios, idx, &image)) {
			nvkm_debug(subdev, "image %d invalid\n", idx);
			return 0;
		}
	}
	nvkm_debug(subdev, "%08x: type %02x, %d bytes\n",
		   image.base, image.type, image.size);

	if (!shadow_fetch(bios, mthd, image.size)) {
		nvkm_debug(subdev, "%08x: fetch failed\n", image.base);
		return 0;
	}

	switch (image.type) {
	case 0x00:
		if (!mthd->func->ignore_checksum &&
		    nvbios_checksum(&bios->data[image.base], image.size)) {
			nvkm_debug(subdev, "%08x: checksum failed\n",
				   image.base);
			if (!mthd->func->require_checksum) {
				if (mthd->func->rw)
					score += 1;
				score += 1;
			} else
				return 0;
		} else {
			score += 3;
		}
		break;
	default:
		score += 3;
		break;
	}

	if (!image.last)
		score += shadow_image(bios, idx + 1, offset + image.size, mthd);
	return score;
}