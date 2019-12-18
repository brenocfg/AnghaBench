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
typedef  scalar_t__ u32 ;
struct camif_vp {int fmt_flags; } ;
struct camif_fmt {int flags; scalar_t__ const fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct camif_fmt*) ; 
 struct camif_fmt* camif_formats ; 

const struct camif_fmt *s3c_camif_find_format(struct camif_vp *vp,
					      const u32 *pixelformat,
					      int index)
{
	const struct camif_fmt *fmt, *def_fmt = NULL;
	unsigned int i;
	int id = 0;

	if (index >= (int)ARRAY_SIZE(camif_formats))
		return NULL;

	for (i = 0; i < ARRAY_SIZE(camif_formats); ++i) {
		fmt = &camif_formats[i];
		if (vp && !(vp->fmt_flags & fmt->flags))
			continue;
		if (pixelformat && fmt->fourcc == *pixelformat)
			return fmt;
		if (index == id)
			def_fmt = fmt;
		id++;
	}
	return def_fmt;
}