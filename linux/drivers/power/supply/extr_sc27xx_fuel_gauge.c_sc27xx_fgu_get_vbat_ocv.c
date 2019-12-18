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
struct sc27xx_fgu_data {int internal_resist; } ;

/* Variables and functions */
 int sc27xx_fgu_get_current (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_vbat_vol (struct sc27xx_fgu_data*,int*) ; 

__attribute__((used)) static int sc27xx_fgu_get_vbat_ocv(struct sc27xx_fgu_data *data, int *val)
{
	int vol, cur, ret;

	ret = sc27xx_fgu_get_vbat_vol(data, &vol);
	if (ret)
		return ret;

	ret = sc27xx_fgu_get_current(data, &cur);
	if (ret)
		return ret;

	/* Return the battery OCV in micro volts. */
	*val = vol * 1000 - cur * data->internal_resist;

	return 0;
}