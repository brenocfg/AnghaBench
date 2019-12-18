#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct nvkm_therm {TYPE_1__* fan; TYPE_2__* func; } ;
struct TYPE_6__ {int min_duty; int max_duty; } ;
struct TYPE_5__ {scalar_t__ (* temp_get ) (struct nvkm_therm*) ;} ;
struct TYPE_4__ {TYPE_3__ bios; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct nvkm_therm*) ; 

__attribute__((used)) static int
nvkm_therm_compute_linear_duty(struct nvkm_therm *therm, u8 linear_min_temp,
                               u8 linear_max_temp)
{
	u8  temp = therm->func->temp_get(therm);
	u16 duty;

	/* handle the non-linear part first */
	if (temp < linear_min_temp)
		return therm->fan->bios.min_duty;
	else if (temp > linear_max_temp)
		return therm->fan->bios.max_duty;

	/* we are in the linear zone */
	duty  = (temp - linear_min_temp);
	duty *= (therm->fan->bios.max_duty - therm->fan->bios.min_duty);
	duty /= (linear_max_temp - linear_min_temp);
	duty += therm->fan->bios.min_duty;
	return duty;
}