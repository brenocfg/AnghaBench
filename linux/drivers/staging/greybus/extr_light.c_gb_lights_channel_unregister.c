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
struct gb_channel {int mode; } ;

/* Variables and functions */
 int GB_CHANNEL_MODE_TORCH ; 
 int /*<<< orphan*/  __gb_lights_flash_led_unregister (struct gb_channel*) ; 
 int /*<<< orphan*/  __gb_lights_led_unregister (struct gb_channel*) ; 
 int /*<<< orphan*/  is_channel_flash (struct gb_channel*) ; 

__attribute__((used)) static void gb_lights_channel_unregister(struct gb_channel *channel)
{
	/* The same as register, handle channels differently */
	if (!is_channel_flash(channel)) {
		__gb_lights_led_unregister(channel);
		return;
	}

	if (channel->mode & GB_CHANNEL_MODE_TORCH)
		__gb_lights_led_unregister(channel);
	else
		__gb_lights_flash_led_unregister(channel);
}