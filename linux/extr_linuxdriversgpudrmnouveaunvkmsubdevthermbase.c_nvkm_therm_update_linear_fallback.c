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
struct TYPE_3__ {int /*<<< orphan*/  temp; } ;
struct TYPE_4__ {TYPE_1__ thrs_fan_boost; } ;
struct nvkm_therm {TYPE_2__ bios_sensor; } ;

/* Variables and functions */
 int nvkm_therm_compute_linear_duty (struct nvkm_therm*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_therm_update_linear_fallback(struct nvkm_therm *therm)
{
	u8 max = therm->bios_sensor.thrs_fan_boost.temp;
	return nvkm_therm_compute_linear_duty(therm, 30, max);
}