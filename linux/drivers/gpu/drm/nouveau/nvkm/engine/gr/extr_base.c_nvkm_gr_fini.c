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
struct TYPE_2__ {int (* fini ) (struct nvkm_gr*,int) ;} ;

/* Variables and functions */
 struct nvkm_gr* nvkm_gr (struct nvkm_engine*) ; 
 int stub1 (struct nvkm_gr*,int) ; 

__attribute__((used)) static int
nvkm_gr_fini(struct nvkm_engine *engine, bool suspend)
{
	struct nvkm_gr *gr = nvkm_gr(engine);
	if (gr->func->fini)
		return gr->func->fini(gr, suspend);
	return 0;
}