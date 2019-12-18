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
struct ti_thermal_data {int sensor_id; struct ti_bandgap* bgp; } ;
struct ti_bandgap {int dummy; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;

/* Variables and functions */
 int THERMAL_TREND_DROPPING ; 
 int THERMAL_TREND_RAISING ; 
 int THERMAL_TREND_STABLE ; 
 int ti_bandgap_get_trend (struct ti_bandgap*,int,int*) ; 

__attribute__((used)) static int __ti_thermal_get_trend(void *p, int trip, enum thermal_trend *trend)
{
	struct ti_thermal_data *data = p;
	struct ti_bandgap *bgp;
	int id, tr, ret = 0;

	bgp = data->bgp;
	id = data->sensor_id;

	ret = ti_bandgap_get_trend(bgp, id, &tr);
	if (ret)
		return ret;

	if (tr > 0)
		*trend = THERMAL_TREND_RAISING;
	else if (tr < 0)
		*trend = THERMAL_TREND_DROPPING;
	else
		*trend = THERMAL_TREND_STABLE;

	return 0;
}