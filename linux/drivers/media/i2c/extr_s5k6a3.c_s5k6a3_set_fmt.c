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
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k6a3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct v4l2_mbus_framefmt* __s5k6a3_get_format (struct s5k6a3*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5k6a3_try_format (struct v4l2_mbus_framefmt*) ; 
 struct s5k6a3* sd_to_s5k6a3 (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k6a3_set_fmt(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_format *fmt)
{
	struct s5k6a3 *sensor = sd_to_s5k6a3(sd);
	struct v4l2_mbus_framefmt *mf;

	s5k6a3_try_format(&fmt->format);

	mf = __s5k6a3_get_format(sensor, cfg, fmt->pad, fmt->which);
	if (mf) {
		mutex_lock(&sensor->lock);
		*mf = fmt->format;
		mutex_unlock(&sensor->lock);
	}
	return 0;
}