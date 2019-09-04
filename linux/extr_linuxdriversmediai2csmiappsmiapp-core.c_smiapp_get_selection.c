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
struct v4l2_subdev_selection {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct smiapp_sensor {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __smiapp_get_selection (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static int smiapp_get_selection(struct v4l2_subdev *subdev,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_selection *sel)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	int rval;

	mutex_lock(&sensor->mutex);
	rval = __smiapp_get_selection(subdev, cfg, sel);
	mutex_unlock(&sensor->mutex);

	return rval;
}