#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device {int dummy; } ;
struct TYPE_7__ {struct nvkm_device* device; } ;
struct nvkm_bar {TYPE_3__ subdev; } ;
struct nv50_bar {TYPE_2__* bar2; TYPE_4__* mem; } ;
struct TYPE_8__ {int addr; } ;
struct TYPE_6__ {TYPE_1__* node; } ;
struct TYPE_5__ {int offset; } ;

/* Variables and functions */
 struct nv50_bar* nv50_bar (struct nvkm_bar*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
nv50_bar_bar2_init(struct nvkm_bar *base)
{
	struct nvkm_device *device = base->subdev.device;
	struct nv50_bar *bar = nv50_bar(base);
	nvkm_wr32(device, 0x001704, 0x00000000 | bar->mem->addr >> 12);
	nvkm_wr32(device, 0x001704, 0x40000000 | bar->mem->addr >> 12);
	nvkm_wr32(device, 0x00170c, 0x80000000 | bar->bar2->node->offset >> 4);
}