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
struct ads1015_data {int /*<<< orphan*/  event_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS1015_CHANNELS ; 

__attribute__((used)) static void ads1015_event_channel_disable(struct ads1015_data *data, int chan)
{
	data->event_channel = ADS1015_CHANNELS;
}