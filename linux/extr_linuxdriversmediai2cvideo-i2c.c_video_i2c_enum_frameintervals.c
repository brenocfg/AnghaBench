#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_i2c_data {TYPE_2__* chip; } ;
struct v4l2_frmsize_discrete {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_3__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_frmivalenum {scalar_t__ index; scalar_t__ width; scalar_t__ height; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_fps; struct v4l2_frmsize_discrete* size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 struct video_i2c_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_i2c_enum_frameintervals(struct file *file, void *priv,
					   struct v4l2_frmivalenum *fe)
{
	const struct video_i2c_data *data = video_drvdata(file);
	const struct v4l2_frmsize_discrete *size = data->chip->size;

	if (fe->index > 0)
		return -EINVAL;

	if (fe->width != size->width || fe->height != size->height)
		return -EINVAL;

	fe->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fe->discrete.numerator = 1;
	fe->discrete.denominator = data->chip->max_fps;

	return 0;
}