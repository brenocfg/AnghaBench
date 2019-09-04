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
struct nvkm_therm_func {int dummy; } ;
struct nvkm_therm {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct gk104_therm {struct gf100_idle_filter const* idle_filter; struct gk104_clkgate_engine_info const* clkgate_order; struct nvkm_therm base; } ;
struct gk104_clkgate_engine_info {int dummy; } ;
struct gf100_idle_filter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gk104_therm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_therm_ctor (struct nvkm_therm*,struct nvkm_device*,int,struct nvkm_therm_func const*) ; 

__attribute__((used)) static int
gk104_therm_new_(const struct nvkm_therm_func *func,
		 struct nvkm_device *device,
		 int index,
		 const struct gk104_clkgate_engine_info *clkgate_order,
		 const struct gf100_idle_filter *idle_filter,
		 struct nvkm_therm **ptherm)
{
	struct gk104_therm *therm = kzalloc(sizeof(*therm), GFP_KERNEL);

	if (!therm)
		return -ENOMEM;

	nvkm_therm_ctor(&therm->base, device, index, func);
	*ptherm = &therm->base;
	therm->clkgate_order = clkgate_order;
	therm->idle_filter = idle_filter;

	return 0;
}