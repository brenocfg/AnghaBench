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
struct sun4i_ts_data {int temp_data; int temp_step; int temp_offset; } ;

/* Variables and functions */
 int EAGAIN ; 

__attribute__((used)) static int sun4i_get_temp(const struct sun4i_ts_data *ts, int *temp)
{
	/* No temp_data until the first irq */
	if (ts->temp_data == -1)
		return -EAGAIN;

	*temp = ts->temp_data * ts->temp_step - ts->temp_offset;

	return 0;
}