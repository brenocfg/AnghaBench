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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_therm {TYPE_2__* fan; } ;
struct TYPE_3__ {int /*<<< orphan*/  linear_max_temp; int /*<<< orphan*/  linear_min_temp; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int nvkm_therm_compute_linear_duty (struct nvkm_therm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_therm_update_linear(struct nvkm_therm *therm)
{
	u8  min = therm->fan->bios.linear_min_temp;
	u8  max = therm->fan->bios.linear_max_temp;
	return nvkm_therm_compute_linear_duty(therm, min, max);
}