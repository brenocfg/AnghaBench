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
struct hid_sensor_common {int timestamp_ns_scale; } ;
typedef  int int64_t ;

/* Variables and functions */

int64_t hid_sensor_convert_timestamp(struct hid_sensor_common *st,
				     int64_t raw_value)
{
	return st->timestamp_ns_scale * raw_value;
}