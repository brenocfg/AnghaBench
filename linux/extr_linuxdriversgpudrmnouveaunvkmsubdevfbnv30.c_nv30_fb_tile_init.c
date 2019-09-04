#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_fb_tile {int addr; int pitch; scalar_t__ limit; } ;
struct nvkm_fb {TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* comp ) (struct nvkm_fb*,int,int,int,struct nvkm_fb_tile*) ;} ;
struct TYPE_4__ {TYPE_1__ tile; } ;

/* Variables and functions */
 scalar_t__ max (unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_fb*,int,int,int,struct nvkm_fb_tile*) ; 

void
nv30_fb_tile_init(struct nvkm_fb *fb, int i, u32 addr, u32 size, u32 pitch,
		  u32 flags, struct nvkm_fb_tile *tile)
{
	/* for performance, select alternate bank offset for zeta */
	if (!(flags & 4)) {
		tile->addr = (0 << 4);
	} else {
		if (fb->func->tile.comp) /* z compression */
			fb->func->tile.comp(fb, i, size, flags, tile);
		tile->addr = (1 << 4);
	}

	tile->addr |= 0x00000001; /* enable */
	tile->addr |= addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
}