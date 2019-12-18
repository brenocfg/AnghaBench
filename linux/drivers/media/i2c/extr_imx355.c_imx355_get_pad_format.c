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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct imx355 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int imx355_do_get_pad_format (struct imx355*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx355* to_imx355 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx355_get_pad_format(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_format *fmt)
{
	struct imx355 *imx355 = to_imx355(sd);
	int ret;

	mutex_lock(&imx355->mutex);
	ret = imx355_do_get_pad_format(imx355, cfg, fmt);
	mutex_unlock(&imx355->mutex);

	return ret;
}