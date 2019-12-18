#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_light {int channels_count; int ready; int has_flash; TYPE_1__* channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int gb_lights_channel_register (TYPE_1__*) ; 
 int gb_lights_light_v4l2_register (struct gb_light*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_lights_light_register(struct gb_light *light)
{
	int ret;
	int i;

	/*
	 * Then, if everything went ok in getting configurations, we register
	 * the classdev, flash classdev and v4l2 subsystem, if a flash device is
	 * found.
	 */
	for (i = 0; i < light->channels_count; i++) {
		ret = gb_lights_channel_register(&light->channels[i]);
		if (ret < 0)
			return ret;

		mutex_init(&light->channels[i].lock);
	}

	light->ready = true;

	if (light->has_flash) {
		ret = gb_lights_light_v4l2_register(light);
		if (ret < 0) {
			light->has_flash = false;
			return ret;
		}
	}

	return 0;
}