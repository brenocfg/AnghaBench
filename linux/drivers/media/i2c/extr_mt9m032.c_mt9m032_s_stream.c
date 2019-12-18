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
struct v4l2_subdev {int dummy; } ;
struct mt9m032 {int streaming; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9m032* to_mt9m032 (struct v4l2_subdev*) ; 
 int update_formatter2 (struct mt9m032*,int) ; 

__attribute__((used)) static int mt9m032_s_stream(struct v4l2_subdev *subdev, int streaming)
{
	struct mt9m032 *sensor = to_mt9m032(subdev);
	int ret;

	mutex_lock(&sensor->lock);
	ret = update_formatter2(sensor, streaming);
	if (!ret)
		sensor->streaming = streaming;
	mutex_unlock(&sensor->lock);

	return ret;
}