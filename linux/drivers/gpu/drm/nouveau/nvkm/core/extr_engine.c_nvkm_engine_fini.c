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
struct nvkm_subdev {int dummy; } ;
struct nvkm_engine {TYPE_1__* func; } ;
struct TYPE_2__ {int (* fini ) (struct nvkm_engine*,int) ;} ;

/* Variables and functions */
 struct nvkm_engine* nvkm_engine (struct nvkm_subdev*) ; 
 int stub1 (struct nvkm_engine*,int) ; 

__attribute__((used)) static int
nvkm_engine_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_engine *engine = nvkm_engine(subdev);
	if (engine->func->fini)
		return engine->func->fini(engine, suspend);
	return 0;
}