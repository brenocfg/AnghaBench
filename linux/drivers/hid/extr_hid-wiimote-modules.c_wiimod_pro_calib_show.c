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
struct TYPE_2__ {int /*<<< orphan*/ * calib_pro_sticks; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct wiimote_data* dev_to_wii (struct device*) ; 
 scalar_t__ sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t wiimod_pro_calib_show(struct device *dev,
				     struct device_attribute *attr,
				     char *out)
{
	struct wiimote_data *wdata = dev_to_wii(dev);
	int r;

	r = 0;
	r += sprintf(&out[r], "%+06hd:", wdata->state.calib_pro_sticks[0]);
	r += sprintf(&out[r], "%+06hd ", wdata->state.calib_pro_sticks[1]);
	r += sprintf(&out[r], "%+06hd:", wdata->state.calib_pro_sticks[2]);
	r += sprintf(&out[r], "%+06hd\n", wdata->state.calib_pro_sticks[3]);

	return r;
}