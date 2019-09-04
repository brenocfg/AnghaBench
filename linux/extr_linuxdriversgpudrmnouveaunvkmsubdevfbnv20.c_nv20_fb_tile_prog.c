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
struct nvkm_fb_tile {int /*<<< orphan*/  zcomp; int /*<<< orphan*/  addr; int /*<<< orphan*/  pitch; int /*<<< orphan*/  limit; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

void
nv20_fb_tile_prog(struct nvkm_fb *fb, int i, struct nvkm_fb_tile *tile)
{
	struct nvkm_device *device = fb->subdev.device;
	nvkm_wr32(device, 0x100244 + (i * 0x10), tile->limit);
	nvkm_wr32(device, 0x100248 + (i * 0x10), tile->pitch);
	nvkm_wr32(device, 0x100240 + (i * 0x10), tile->addr);
	nvkm_rd32(device, 0x100240 + (i * 0x10));
	nvkm_wr32(device, 0x100300 + (i * 0x04), tile->zcomp);
}