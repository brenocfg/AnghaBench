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
typedef  int u32 ;
struct nvkm_fb_tile {int addr; int pitch; scalar_t__ limit; } ;
struct nvkm_fb {int dummy; } ;

/* Variables and functions */
 scalar_t__ max (unsigned int,int) ; 

__attribute__((used)) static void
nv44_fb_tile_init(struct nvkm_fb *fb, int i, u32 addr, u32 size, u32 pitch,
		  u32 flags, struct nvkm_fb_tile *tile)
{
	tile->addr  = 0x00000001; /* mode = vram */
	tile->addr |= addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
}