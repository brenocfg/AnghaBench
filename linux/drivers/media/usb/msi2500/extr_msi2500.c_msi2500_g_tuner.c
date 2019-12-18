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
struct v4l2_tuner {int index; int capability; int rangelow; int rangehigh; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct msi2500_dev {int /*<<< orphan*/  v4l2_subdev; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ADC ; 
 int V4L2_TUNER_CAP_1HZ ; 
 int V4L2_TUNER_CAP_FREQ_BANDS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 struct msi2500_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int msi2500_g_tuner(struct file *file, void *priv, struct v4l2_tuner *v)
{
	struct msi2500_dev *dev = video_drvdata(file);
	int ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	if (v->index == 0) {
		strscpy(v->name, "Mirics MSi2500", sizeof(v->name));
		v->type = V4L2_TUNER_ADC;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow =   1200000;
		v->rangehigh = 15000000;
		ret = 0;
	} else if (v->index == 1) {
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_tuner, v);
	} else {
		ret = -EINVAL;
	}

	return ret;
}