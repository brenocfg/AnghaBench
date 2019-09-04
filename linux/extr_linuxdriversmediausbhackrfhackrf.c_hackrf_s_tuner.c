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
struct v4l2_tuner {int index; } ;
struct hackrf_dev {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct hackrf_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int hackrf_s_tuner(struct file *file, void *priv,
		const struct v4l2_tuner *v)
{
	struct hackrf_dev *dev = video_drvdata(file);
	int ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0)
		ret = 0;
	else if (v->index == 1)
		ret = 0;
	else
		ret = -EINVAL;

	return ret;
}