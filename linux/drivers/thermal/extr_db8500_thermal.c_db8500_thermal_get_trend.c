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
struct db8500_thermal_zone {int trend; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;

/* Variables and functions */

__attribute__((used)) static int db8500_thermal_get_trend(void *data, int trip, enum thermal_trend *trend)
{
	struct db8500_thermal_zone *th = data;

	*trend = th->trend;

	return 0;
}