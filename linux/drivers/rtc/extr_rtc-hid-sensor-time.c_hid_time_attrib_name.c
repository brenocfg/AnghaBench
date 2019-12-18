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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 unsigned int TIME_RTC_CHANNEL_MAX ; 
 scalar_t__* hid_time_addresses ; 
 char const** hid_time_channel_names ; 

__attribute__((used)) static const char *hid_time_attrib_name(u32 attrib_id)
{
	static const char unknown[] = "unknown";
	unsigned i;

	for (i = 0; i < TIME_RTC_CHANNEL_MAX; ++i) {
		if (hid_time_addresses[i] == attrib_id)
			return hid_time_channel_names[i];
	}
	return unknown; /* should never happen */
}