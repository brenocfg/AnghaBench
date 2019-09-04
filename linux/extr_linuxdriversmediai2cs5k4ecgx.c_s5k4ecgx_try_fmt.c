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
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct s5k4ecgx_pixfmt {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct s5k4ecgx_pixfmt const*) ; 
 struct s5k4ecgx_pixfmt const* s5k4ecgx_formats ; 

__attribute__((used)) static const struct s5k4ecgx_pixfmt *s5k4ecgx_try_fmt(struct v4l2_subdev *sd,
					    struct v4l2_mbus_framefmt *mf)
{
	int i = ARRAY_SIZE(s5k4ecgx_formats);

	while (--i)
		if (mf->code == s5k4ecgx_formats[i].code)
			break;
	mf->code = s5k4ecgx_formats[i].code;

	return &s5k4ecgx_formats[i];
}