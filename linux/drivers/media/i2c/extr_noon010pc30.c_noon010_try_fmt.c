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
struct noon010_format {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct noon010_format const*) ; 
 struct noon010_format const* noon010_formats ; 

__attribute__((used)) static const struct noon010_format *noon010_try_fmt(struct v4l2_subdev *sd,
					    struct v4l2_mbus_framefmt *mf)
{
	int i = ARRAY_SIZE(noon010_formats);

	while (--i)
		if (mf->code == noon010_formats[i].code)
			break;
	mf->code = noon010_formats[i].code;

	return &noon010_formats[i];
}