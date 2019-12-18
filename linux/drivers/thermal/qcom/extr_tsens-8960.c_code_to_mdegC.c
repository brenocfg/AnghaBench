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
typedef  int u32 ;
struct tsens_sensor {int offset; int /*<<< orphan*/  tzd; } ;

/* Variables and functions */
 int CAL_MDEGC ; 
 int thermal_zone_get_slope (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int code_to_mdegC(u32 adc_code, const struct tsens_sensor *s)
{
	int slope, offset;

	slope = thermal_zone_get_slope(s->tzd);
	offset = CAL_MDEGC - slope * s->offset;

	return adc_code * slope + offset;
}