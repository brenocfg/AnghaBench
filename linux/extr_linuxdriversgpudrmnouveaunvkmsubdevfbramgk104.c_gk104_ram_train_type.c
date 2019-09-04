#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_ram {TYPE_3__* fb; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0209S {size_t* data; } ;
struct nvbios_M0209E {int v02_07; int v03; } ;
struct nvbios_M0205S {int data; } ;
struct nvbios_M0205E {int type; } ;
struct gk104_ram_train {int mask; struct nvbios_M0209S type09; struct nvbios_M0209S type08; struct nvbios_M0209S type07; struct nvbios_M0209S type06; struct nvbios_M0209S type04; struct nvbios_M0209S type01; struct nvbios_M0209S type00; struct nvbios_M0209S remap; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ subdev; } ;
struct TYPE_4__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  nvbios_M0205Ep (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0205E*) ; 
 int /*<<< orphan*/  nvbios_M0205Sp (struct nvkm_bios*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0205S*) ; 
 int /*<<< orphan*/  nvbios_M0209Ep (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0209E*) ; 
 int /*<<< orphan*/  nvbios_M0209Sp (struct nvkm_bios*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0209S*) ; 

__attribute__((used)) static int
gk104_ram_train_type(struct nvkm_ram *ram, int i, u8 ramcfg,
		     struct gk104_ram_train *train)
{
	struct nvkm_bios *bios = ram->fb->subdev.device->bios;
	struct nvbios_M0205E M0205E;
	struct nvbios_M0205S M0205S;
	struct nvbios_M0209E M0209E;
	struct nvbios_M0209S *remap = &train->remap;
	struct nvbios_M0209S *value;
	u8  ver, hdr, cnt, len;
	u32 data;

	/* determine type of data for this index */
	if (!(data = nvbios_M0205Ep(bios, i, &ver, &hdr, &cnt, &len, &M0205E)))
		return -ENOENT;

	switch (M0205E.type) {
	case 0x00: value = &train->type00; break;
	case 0x01: value = &train->type01; break;
	case 0x04: value = &train->type04; break;
	case 0x06: value = &train->type06; break;
	case 0x07: value = &train->type07; break;
	case 0x08: value = &train->type08; break;
	case 0x09: value = &train->type09; break;
	default:
		return 0;
	}

	/* training data index determined by ramcfg strap */
	if (!(data = nvbios_M0205Sp(bios, i, ramcfg, &ver, &hdr, &M0205S)))
		return -EINVAL;
	i = M0205S.data;

	/* training data format information */
	if (!(data = nvbios_M0209Ep(bios, i, &ver, &hdr, &cnt, &len, &M0209E)))
		return -EINVAL;

	/* ... and the raw data */
	if (!(data = nvbios_M0209Sp(bios, i, 0, &ver, &hdr, value)))
		return -EINVAL;

	if (M0209E.v02_07 == 2) {
		/* of course! why wouldn't we have a pointer to another entry
		 * in the same table, and use the first one as an array of
		 * remap indices...
		 */
		if (!(data = nvbios_M0209Sp(bios, M0209E.v03, 0, &ver, &hdr,
					    remap)))
			return -EINVAL;

		for (i = 0; i < ARRAY_SIZE(value->data); i++)
			value->data[i] = remap->data[value->data[i]];
	} else
	if (M0209E.v02_07 != 1)
		return -EINVAL;

	train->mask |= 1 << M0205E.type;
	return 0;
}