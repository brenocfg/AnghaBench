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
struct v4l2_frequency {int tuner; int /*<<< orphan*/  type; int /*<<< orphan*/  frequency; } ;
struct msi2500_dev {int /*<<< orphan*/  v4l2_subdev; int /*<<< orphan*/  f_adc; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_RF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 struct msi2500_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int msi2500_g_frequency(struct file *file, void *priv,
			       struct v4l2_frequency *f)
{
	struct msi2500_dev *dev = video_drvdata(file);
	int ret  = 0;

	dev_dbg(dev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	if (f->tuner == 0) {
		f->frequency = dev->f_adc;
		ret = 0;
	} else if (f->tuner == 1) {
		f->type = V4L2_TUNER_RF;
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, g_frequency, f);
	} else {
		ret = -EINVAL;
	}

	return ret;
}