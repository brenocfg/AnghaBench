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
struct nvkm_therm_clkgate_pack {int dummy; } ;
struct nvkm_therm {TYPE_1__* func; int /*<<< orphan*/  clkgating_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clkgate_init ) (struct nvkm_therm*,struct nvkm_therm_clkgate_pack const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_therm*,struct nvkm_therm_clkgate_pack const*) ; 

void
nvkm_therm_clkgate_init(struct nvkm_therm *therm,
			const struct nvkm_therm_clkgate_pack *p)
{
	if (!therm || !therm->func->clkgate_init || !therm->clkgating_enabled)
		return;

	therm->func->clkgate_init(therm, p);
}