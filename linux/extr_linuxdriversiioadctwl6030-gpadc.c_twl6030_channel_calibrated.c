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
struct twl6030_ideal_code {int code2; } ;
struct twl6030_gpadc_platform_data {struct twl6030_ideal_code* ideal; int /*<<< orphan*/  nchannels; } ;

/* Variables and functions */
 int twl6030_gpadc_lookup (struct twl6030_ideal_code const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_channel_calibrated(const struct twl6030_gpadc_platform_data
		*pdata, int channel)
{
	const struct twl6030_ideal_code *ideal = pdata->ideal;
	int i;

	i = twl6030_gpadc_lookup(ideal, channel, pdata->nchannels);
	/* not calibrated channels have 0 in all structure members */
	return pdata->ideal[i].code2;
}