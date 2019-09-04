#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_therm {TYPE_1__* func; scalar_t__ fan; } ;
struct TYPE_4__ {int /*<<< orphan*/  line; } ;
struct nvkm_fantog {TYPE_2__ func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pwm_ctrl ) (struct nvkm_therm*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_fantog_update (struct nvkm_fantog*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_therm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_fantog_set(struct nvkm_therm *therm, int percent)
{
	struct nvkm_fantog *fan = (void *)therm->fan;
	if (therm->func->pwm_ctrl)
		therm->func->pwm_ctrl(therm, fan->func.line, false);
	nvkm_fantog_update(fan, percent);
	return 0;
}