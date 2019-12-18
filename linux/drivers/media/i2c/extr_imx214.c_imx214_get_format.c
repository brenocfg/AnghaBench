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
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;
struct imx214 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __imx214_get_pad_format (struct imx214*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx214* to_imx214 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx214_get_format(struct v4l2_subdev *sd,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_format *format)
{
	struct imx214 *imx214 = to_imx214(sd);

	mutex_lock(&imx214->mutex);
	format->format = *__imx214_get_pad_format(imx214, cfg, format->pad,
						  format->which);
	mutex_unlock(&imx214->mutex);

	return 0;
}