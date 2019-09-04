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
struct ams_iaqcore_data {scalar_t__ last_update; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int ams_iaqcore_read_measurement (struct ams_iaqcore_data*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ams_iaqcore_get_measurement(struct ams_iaqcore_data *data)
{
	int ret;

	/* sensor can only be polled once a second max per datasheet */
	if (!time_after(jiffies, data->last_update + HZ))
		return 0;

	ret = ams_iaqcore_read_measurement(data);
	if (ret < 0)
		return ret;

	data->last_update = jiffies;

	return 0;
}