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
struct v4l2_tuner {scalar_t__ index; } ;
struct file {int dummy; } ;
struct em28xx {TYPE_1__* v4l2; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner const*) ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_s_tuner(struct file *file, void *priv,
			 const struct v4l2_tuner *t)
{
	struct em28xx *dev = video_drvdata(file);

	if (t->index != 0)
		return -EINVAL;

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, tuner, s_tuner, t);

	return 0;
}