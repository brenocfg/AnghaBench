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
struct nvkm_therm {int /*<<< orphan*/  subdev; int /*<<< orphan*/  clkgating_enabled; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  clkgate_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
nvkm_therm_clkgate_oneinit(struct nvkm_therm *therm)
{
	if (!therm->func->clkgate_enable || !therm->clkgating_enabled)
		return;

	nvkm_info(&therm->subdev, "Clockgating enabled\n");
}