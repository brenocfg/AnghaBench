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
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa711x_set_lcr (struct v4l2_subdev*,struct v4l2_sliced_vbi_format*) ; 

__attribute__((used)) static int saa711x_s_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *fmt)
{
	saa711x_set_lcr(sd, fmt);
	return 0;
}