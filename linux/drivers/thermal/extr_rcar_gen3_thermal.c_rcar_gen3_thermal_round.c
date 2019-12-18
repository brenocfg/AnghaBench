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

/* Variables and functions */
 int RCAR3_THERMAL_GRAN ; 

__attribute__((used)) static int rcar_gen3_thermal_round(int temp)
{
	int result, round_offs;

	round_offs = temp >= 0 ? RCAR3_THERMAL_GRAN / 2 :
		-RCAR3_THERMAL_GRAN / 2;
	result = (temp + round_offs) / RCAR3_THERMAL_GRAN;
	return result * RCAR3_THERMAL_GRAN;
}