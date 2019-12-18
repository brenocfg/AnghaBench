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
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  index; } ;
struct gsc_fmt {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gsc_fmt* find_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gsc_enum_fmt(struct v4l2_fmtdesc *f)
{
	const struct gsc_fmt *fmt;

	fmt = find_fmt(NULL, NULL, f->index);
	if (!fmt)
		return -EINVAL;

	f->pixelformat = fmt->pixelformat;

	return 0;
}