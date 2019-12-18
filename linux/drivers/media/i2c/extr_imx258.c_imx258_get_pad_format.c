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
struct imx258 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __imx258_get_pad_format (struct imx258*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx258* to_imx258 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx258_get_pad_format(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_format *fmt)
{
	struct imx258 *imx258 = to_imx258(sd);
	int ret;

	mutex_lock(&imx258->mutex);
	ret = __imx258_get_pad_format(imx258, cfg, fmt);
	mutex_unlock(&imx258->mutex);

	return ret;
}