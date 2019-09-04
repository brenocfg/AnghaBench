#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int denominator; int numerator; } ;
struct v4l2_subdev_frame_interval {TYPE_2__ interval; } ;
struct v4l2_mbus_framefmt {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct s5k6aa_interval {int reg_fr_time; TYPE_3__ size; } ;
struct s5k6aa {int /*<<< orphan*/  sd; struct s5k6aa_interval const* fiv; TYPE_1__* preset; } ;
struct TYPE_4__ {struct v4l2_mbus_framefmt mbus_fmt; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct s5k6aa_interval*) ; 
 int EINVAL ; 
 unsigned int UINT_MAX ; 
 unsigned int abs (int) ; 
 int /*<<< orphan*/  debug ; 
 struct s5k6aa_interval* s5k6aa_intervals ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int __s5k6aa_set_frame_interval(struct s5k6aa *s5k6aa,
				       struct v4l2_subdev_frame_interval *fi)
{
	struct v4l2_mbus_framefmt *mbus_fmt = &s5k6aa->preset->mbus_fmt;
	const struct s5k6aa_interval *fiv = &s5k6aa_intervals[0];
	unsigned int err, min_err = UINT_MAX;
	unsigned int i, fr_time;

	if (fi->interval.denominator == 0)
		return -EINVAL;

	fr_time = fi->interval.numerator * 10000 / fi->interval.denominator;

	for (i = 0; i < ARRAY_SIZE(s5k6aa_intervals); i++) {
		const struct s5k6aa_interval *iv = &s5k6aa_intervals[i];

		if (mbus_fmt->width > iv->size.width ||
		    mbus_fmt->height > iv->size.height)
			continue;

		err = abs(iv->reg_fr_time - fr_time);
		if (err < min_err) {
			fiv = iv;
			min_err = err;
		}
	}
	s5k6aa->fiv = fiv;

	v4l2_dbg(1, debug, &s5k6aa->sd, "Changed frame interval to %d us\n",
		 fiv->reg_fr_time * 100);
	return 0;
}