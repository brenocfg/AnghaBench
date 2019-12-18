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
struct v4l2_subdev_format {int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;
struct stimx274 {int /*<<< orphan*/  lock; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stimx274* to_imx274 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx274_get_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct stimx274 *imx274 = to_imx274(sd);

	mutex_lock(&imx274->lock);
	fmt->format = imx274->format;
	mutex_unlock(&imx274->lock);
	return 0;
}