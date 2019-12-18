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
struct gb_channel {scalar_t__ releasing; } ;

/* Variables and functions */
 int __gb_lights_flash_brightness_set (struct gb_channel*) ; 
 int __gb_lights_led_brightness_set (struct gb_channel*) ; 
 scalar_t__ is_channel_flash (struct gb_channel*) ; 

__attribute__((used)) static int __gb_lights_brightness_set(struct gb_channel *channel)
{
	int ret;

	if (channel->releasing)
		return 0;

	if (is_channel_flash(channel))
		ret = __gb_lights_flash_brightness_set(channel);
	else
		ret = __gb_lights_led_brightness_set(channel);

	return ret;
}