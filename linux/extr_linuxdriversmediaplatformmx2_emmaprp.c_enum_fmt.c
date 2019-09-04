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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct emmaprp_fmt {int types; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_FORMATS ; 
 struct emmaprp_fmt* formats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int enum_fmt(struct v4l2_fmtdesc *f, u32 type)
{
	int i, num;
	struct emmaprp_fmt *fmt;

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
		strlcpy(f->description, fmt->name, sizeof(f->description) - 1);
		f->pixelformat = fmt->fourcc;
		return 0;
	}

	/* Format not found */
	return -EINVAL;
}