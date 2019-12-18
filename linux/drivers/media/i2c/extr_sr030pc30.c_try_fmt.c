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
struct sr030pc30_format {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sr030pc30_format const*) ; 
 struct sr030pc30_format const* sr030pc30_formats ; 
 int /*<<< orphan*/  sr030pc30_try_frame_size (struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static const struct sr030pc30_format *try_fmt(struct v4l2_subdev *sd,
					      struct v4l2_mbus_framefmt *mf)
{
	int i;

	sr030pc30_try_frame_size(mf);

	for (i = 0; i < ARRAY_SIZE(sr030pc30_formats); i++) {
		if (mf->code == sr030pc30_formats[i].code)
			break;
	}
	if (i == ARRAY_SIZE(sr030pc30_formats))
		i = 0;

	mf->code = sr030pc30_formats[i].code;

	return &sr030pc30_formats[i];
}