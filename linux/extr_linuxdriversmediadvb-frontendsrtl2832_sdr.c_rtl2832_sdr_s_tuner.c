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
struct rtl2832_sdr_dev {int /*<<< orphan*/  v4l2_subdev; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_HAS_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner const*) ; 
 struct rtl2832_sdr_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rtl2832_sdr_s_tuner(struct file *file, void *priv,
		const struct v4l2_tuner *v)
{
	struct rtl2832_sdr_dev *dev = video_drvdata(file);
	struct platform_device *pdev = dev->pdev;
	int ret;

	dev_dbg(&pdev->dev, "\n");

	if (v->index == 0) {
		ret = 0;
	} else if (v->index == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, s_tuner)) {
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, s_tuner, v);
	} else if (v->index == 1) {
		ret = 0;
	} else {
		ret = -EINVAL;
	}
	return ret;
}