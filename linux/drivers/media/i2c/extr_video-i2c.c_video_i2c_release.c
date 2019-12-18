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
struct video_i2c_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; } ;
struct video_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct video_i2c_data*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 struct video_i2c_data* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void video_i2c_release(struct video_device *vdev)
{
	struct video_i2c_data *data = video_get_drvdata(vdev);

	v4l2_device_unregister(&data->v4l2_dev);
	mutex_destroy(&data->lock);
	mutex_destroy(&data->queue_lock);
	regmap_exit(data->regmap);
	kfree(data);
}