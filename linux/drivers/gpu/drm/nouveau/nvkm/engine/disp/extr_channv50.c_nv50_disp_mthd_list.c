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
typedef  scalar_t__ u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct nv50_disp_mthd_list {int mthd; TYPE_3__* data; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {TYPE_1__ engine; } ;
struct nv50_disp {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  mods ;
struct TYPE_6__ {scalar_t__ mthd; scalar_t__ addr; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  info ; 
 int /*<<< orphan*/  nvkm_printk_ (struct nvkm_subdev*,int,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,char*,char*,char const*) ; 
 scalar_t__ nvkm_rd32 (struct nvkm_device*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 

__attribute__((used)) static void
nv50_disp_mthd_list(struct nv50_disp *disp, int debug, u32 base, int c,
		    const struct nv50_disp_mthd_list *list, int inst)
{
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int i;

	for (i = 0; list->data[i].mthd; i++) {
		if (list->data[i].addr) {
			u32 next = nvkm_rd32(device, list->data[i].addr + base + 0);
			u32 prev = nvkm_rd32(device, list->data[i].addr + base + c);
			u32 mthd = list->data[i].mthd + (list->mthd * inst);
			const char *name = list->data[i].name;
			char mods[16];

			if (prev != next)
				snprintf(mods, sizeof(mods), "-> %08x", next);
			else
				snprintf(mods, sizeof(mods), "%13c", ' ');

			nvkm_printk_(subdev, debug, info,
				     "\t%04x: %08x %s%s%s\n",
				     mthd, prev, mods, name ? " // " : "",
				     name ? name : "");
		}
	}
}