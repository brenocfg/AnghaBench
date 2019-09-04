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
typedef  int u64 ;
struct TYPE_4__ {int /*<<< orphan*/  denominator; scalar_t__ numerator; } ;
struct v4l2_subdev_frame_interval {TYPE_1__ interval; } ;
struct v4l2_mbus_framefmt {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_6__ {int numerator; int denominator; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; } ;
struct ov965x_interval {TYPE_3__ interval; TYPE_2__ size; } ;
struct ov965x {int /*<<< orphan*/  sd; struct ov965x_interval const* fiv; struct v4l2_mbus_framefmt format; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ov965x_interval*) ; 
 int EINVAL ; 
 int abs (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 struct ov965x_interval* ov965x_intervals ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int __ov965x_set_frame_interval(struct ov965x *ov965x,
				       struct v4l2_subdev_frame_interval *fi)
{
	struct v4l2_mbus_framefmt *mbus_fmt = &ov965x->format;
	const struct ov965x_interval *fiv = &ov965x_intervals[0];
	u64 req_int, err, min_err = ~0ULL;
	unsigned int i;

	if (fi->interval.denominator == 0)
		return -EINVAL;

	req_int = (u64)fi->interval.numerator * 10000;
	do_div(req_int, fi->interval.denominator);

	for (i = 0; i < ARRAY_SIZE(ov965x_intervals); i++) {
		const struct ov965x_interval *iv = &ov965x_intervals[i];

		if (mbus_fmt->width != iv->size.width ||
		    mbus_fmt->height != iv->size.height)
			continue;
		err = abs((u64)(iv->interval.numerator * 10000) /
			    iv->interval.denominator - req_int);
		if (err < min_err) {
			fiv = iv;
			min_err = err;
		}
	}
	ov965x->fiv = fiv;

	v4l2_dbg(1, debug, &ov965x->sd, "Changed frame interval to %u us\n",
		 fiv->interval.numerator * 1000000 / fiv->interval.denominator);

	return 0;
}