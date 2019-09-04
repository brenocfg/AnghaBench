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
struct nvkm_engine {int dummy; } ;
struct TYPE_2__ {int (* chsw_load ) (struct nvkm_gr*) ;} ;

/* Variables and functions */
 struct nvkm_gr* nvkm_gr (struct nvkm_engine*) ; 
 int stub1 (struct nvkm_gr*) ; 

__attribute__((used)) static bool
nvkm_gr_chsw_load(struct nvkm_engine *engine)
{
	struct nvkm_gr *gr = nvkm_gr(engine);
	if (gr->func->chsw_load)
		return gr->func->chsw_load(gr);
	return false;
}