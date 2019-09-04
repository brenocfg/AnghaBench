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
struct nvkm_therm {TYPE_1__* fan; } ;
struct TYPE_4__ {int min_duty; int max_duty; } ;
struct TYPE_3__ {TYPE_2__ bios; } ;

/* Variables and functions */

__attribute__((used)) static void
nvkm_therm_fan_safety_checks(struct nvkm_therm *therm)
{
	if (therm->fan->bios.min_duty > 100)
		therm->fan->bios.min_duty = 100;
	if (therm->fan->bios.max_duty > 100)
		therm->fan->bios.max_duty = 100;

	if (therm->fan->bios.min_duty > therm->fan->bios.max_duty)
		therm->fan->bios.min_duty = therm->fan->bios.max_duty;
}