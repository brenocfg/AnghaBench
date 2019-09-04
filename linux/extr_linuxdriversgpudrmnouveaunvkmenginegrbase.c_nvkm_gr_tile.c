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
struct nvkm_gr {TYPE_1__* func; } ;
struct nvkm_fb_tile {int dummy; } ;
struct nvkm_engine {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tile ) (struct nvkm_gr*,int,struct nvkm_fb_tile*) ;} ;

/* Variables and functions */
 struct nvkm_gr* nvkm_gr (struct nvkm_engine*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_gr*,int,struct nvkm_fb_tile*) ; 

__attribute__((used)) static void
nvkm_gr_tile(struct nvkm_engine *engine, int region, struct nvkm_fb_tile *tile)
{
	struct nvkm_gr *gr = nvkm_gr(engine);
	if (gr->func->tile)
		gr->func->tile(gr, region, tile);
}