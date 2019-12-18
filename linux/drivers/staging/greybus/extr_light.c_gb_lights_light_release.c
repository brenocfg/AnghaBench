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
struct gb_light {int ready; int has_flash; int channels_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_lights_channel_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_lights_light_v4l2_unregister (struct gb_light*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_lights_light_release(struct gb_light *light)
{
	int i;

	light->ready = false;

	if (light->has_flash)
		gb_lights_light_v4l2_unregister(light);
	light->has_flash = false;

	for (i = 0; i < light->channels_count; i++)
		gb_lights_channel_release(&light->channels[i]);
	light->channels_count = 0;

	kfree(light->channels);
	light->channels = NULL;
	kfree(light->name);
	light->name = NULL;
}