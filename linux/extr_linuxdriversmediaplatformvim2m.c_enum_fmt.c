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
typedef  int u32 ;
struct vim2m_fmt {int types; int /*<<< orphan*/  fourcc; } ;
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_FORMATS ; 
 struct vim2m_fmt* formats ; 

__attribute__((used)) static int enum_fmt(struct v4l2_fmtdesc *f, u32 type)
{
	int i, num;
	struct vim2m_fmt *fmt;

	num = 0;

	for (i = 0; i < NUM_FORMATS; ++i) {
		if (formats[i].types & type) {
			/* index-th format of type type found ? */
			if (num == f->index)
				break;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index */
			++num;
		}
	}

	if (i < NUM_FORMATS) {
		/* Format found */
		fmt = &formats[i];
		f->pixelformat = fmt->fourcc;
		return 0;
	}

	/* Format not found */
	return -EINVAL;
}