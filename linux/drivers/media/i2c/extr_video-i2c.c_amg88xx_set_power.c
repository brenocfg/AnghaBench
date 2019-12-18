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
struct video_i2c_data {int dummy; } ;

/* Variables and functions */
 int amg88xx_set_power_off (struct video_i2c_data*) ; 
 int amg88xx_set_power_on (struct video_i2c_data*) ; 

__attribute__((used)) static int amg88xx_set_power(struct video_i2c_data *data, bool on)
{
	if (on)
		return amg88xx_set_power_on(data);

	return amg88xx_set_power_off(data);
}