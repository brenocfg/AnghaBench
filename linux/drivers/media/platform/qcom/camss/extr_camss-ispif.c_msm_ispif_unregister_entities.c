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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct ispif_device {int line_num; TYPE_1__* line; int /*<<< orphan*/  config_lock; int /*<<< orphan*/  power_lock; } ;
struct TYPE_2__ {struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

void msm_ispif_unregister_entities(struct ispif_device *ispif)
{
	int i;

	mutex_destroy(&ispif->power_lock);
	mutex_destroy(&ispif->config_lock);

	for (i = 0; i < ispif->line_num; i++) {
		struct v4l2_subdev *sd = &ispif->line[i].subdev;

		v4l2_device_unregister_subdev(sd);
		media_entity_cleanup(&sd->entity);
	}
}