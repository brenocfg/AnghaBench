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
struct rcar_gen3_thermal_tsc {int low; int high; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GEN3_IRQTEMP1 ; 
 int /*<<< orphan*/  REG_GEN3_IRQTEMP2 ; 
 int clamp_val (int,int,int) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_mcelsius_to_temp (struct rcar_gen3_thermal_tsc*,int) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_write (struct rcar_gen3_thermal_tsc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_gen3_thermal_set_trips(void *devdata, int low, int high)
{
	struct rcar_gen3_thermal_tsc *tsc = devdata;

	low = clamp_val(low, -40000, 120000);
	high = clamp_val(high, -40000, 120000);

	rcar_gen3_thermal_write(tsc, REG_GEN3_IRQTEMP1,
				rcar_gen3_thermal_mcelsius_to_temp(tsc, low));

	rcar_gen3_thermal_write(tsc, REG_GEN3_IRQTEMP2,
				rcar_gen3_thermal_mcelsius_to_temp(tsc, high));

	tsc->low = low;
	tsc->high = high;

	return 0;
}