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
struct nvkm_fb_tile {int /*<<< orphan*/  tag; scalar_t__ zcomp; scalar_t__ pitch; scalar_t__ limit; scalar_t__ addr; } ;
struct nvkm_fb {int /*<<< orphan*/  tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nv20_fb_tile_fini(struct nvkm_fb *fb, int i, struct nvkm_fb_tile *tile)
{
	tile->addr  = 0;
	tile->limit = 0;
	tile->pitch = 0;
	tile->zcomp = 0;
	nvkm_mm_free(&fb->tags, &tile->tag);
}