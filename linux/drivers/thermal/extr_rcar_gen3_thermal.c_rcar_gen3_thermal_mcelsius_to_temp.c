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
struct TYPE_2__ {int a1; int b1; int a2; int b2; } ;
struct rcar_gen3_thermal_tsc {int tj_t; TYPE_1__ coef; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int INT_FIXPT (int) ; 

__attribute__((used)) static int rcar_gen3_thermal_mcelsius_to_temp(struct rcar_gen3_thermal_tsc *tsc,
					      int mcelsius)
{
	int celsius, val;

	celsius = DIV_ROUND_CLOSEST(mcelsius, 1000);
	if (celsius <= INT_FIXPT(tsc->tj_t))
		val = celsius * tsc->coef.a1 + tsc->coef.b1;
	else
		val = celsius * tsc->coef.a2 + tsc->coef.b2;

	return INT_FIXPT(val);
}