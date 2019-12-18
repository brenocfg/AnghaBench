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
struct nvkm_fb_tile {int dummy; } ;
struct nvkm_fb {TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini ) (struct nvkm_fb*,int,struct nvkm_fb_tile*) ;} ;
struct TYPE_4__ {TYPE_1__ tile; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_fb*,int,struct nvkm_fb_tile*) ; 

void
nvkm_fb_tile_fini(struct nvkm_fb *fb, int region, struct nvkm_fb_tile *tile)
{
	fb->func->tile.fini(fb, region, tile);
}