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
struct ads1015_data {scalar_t__ event_channel; } ;

/* Variables and functions */
 scalar_t__ ADS1015_CHANNELS ; 

__attribute__((used)) static bool ads1015_event_channel_enabled(struct ads1015_data *data)
{
	return (data->event_channel != ADS1015_CHANNELS);
}