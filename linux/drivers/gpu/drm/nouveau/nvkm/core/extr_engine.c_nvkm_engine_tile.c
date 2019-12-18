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
struct TYPE_8__ {int /*<<< orphan*/ * region; } ;
struct nvkm_fb {TYPE_4__ tile; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct nvkm_engine {TYPE_3__* func; TYPE_2__ subdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* tile ) (struct nvkm_engine*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct nvkm_fb* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_engine*,int,int /*<<< orphan*/ *) ; 

void
nvkm_engine_tile(struct nvkm_engine *engine, int region)
{
	struct nvkm_fb *fb = engine->subdev.device->fb;
	if (engine->func->tile)
		engine->func->tile(engine, region, &fb->tile.region[region]);
}