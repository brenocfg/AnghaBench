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
struct nvkm_fb_tile {int zcomp; TYPE_2__* tag; } ;
struct nvkm_fb {int /*<<< orphan*/  tags; TYPE_1__* ram; } ;
struct TYPE_4__ {int offset; } ;
struct TYPE_3__ {int parts; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  nvkm_mm_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,TYPE_2__**) ; 
 int round_up (int,int) ; 

__attribute__((used)) static void
nv35_fb_tile_comp(struct nvkm_fb *fb, int i, u32 size, u32 flags,
		  struct nvkm_fb_tile *tile)
{
	u32 tiles = DIV_ROUND_UP(size, 0x40);
	u32 tags  = round_up(tiles / fb->ram->parts, 0x40);
	if (!nvkm_mm_head(&fb->tags, 0, 1, tags, tags, 1, &tile->tag)) {
		if (flags & 2) tile->zcomp |= 0x04000000; /* Z16 */
		else           tile->zcomp |= 0x08000000; /* Z24S8 */
		tile->zcomp |= ((tile->tag->offset           ) >> 6);
		tile->zcomp |= ((tile->tag->offset + tags - 1) >> 6) << 13;
#ifdef __BIG_ENDIAN
		tile->zcomp |= 0x40000000;
#endif
	}
}