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
struct nvkm_engine {TYPE_1__* func; } ;
struct TYPE_2__ {int (* chsw_load ) (struct nvkm_engine*) ;} ;

/* Variables and functions */
 int stub1 (struct nvkm_engine*) ; 

bool
nvkm_engine_chsw_load(struct nvkm_engine *engine)
{
	if (engine->func->chsw_load)
		return engine->func->chsw_load(engine);
	return false;
}