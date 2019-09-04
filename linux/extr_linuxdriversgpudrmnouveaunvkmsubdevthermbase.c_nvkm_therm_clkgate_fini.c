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
struct nvkm_therm {TYPE_1__* func; int /*<<< orphan*/  subdev; int /*<<< orphan*/  clkgating_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clkgate_fini ) (struct nvkm_therm*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_therm*,int) ; 

void
nvkm_therm_clkgate_fini(struct nvkm_therm *therm, bool suspend)
{
	if (!therm || !therm->func->clkgate_fini || !therm->clkgating_enabled)
		return;

	nvkm_debug(&therm->subdev,
		   "Preparing clockgating for %s\n",
		   suspend ? "suspend" : "fini");
	therm->func->clkgate_fini(therm, suspend);
}