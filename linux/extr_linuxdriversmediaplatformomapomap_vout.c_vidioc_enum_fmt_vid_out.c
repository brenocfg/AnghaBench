#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_OUTPUT_FORMATS ; 
 TYPE_1__* omap_formats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_out(struct file *file, void *fh,
			struct v4l2_fmtdesc *fmt)
{
	int index = fmt->index;

	if (index >= NUM_OUTPUT_FORMATS)
		return -EINVAL;

	fmt->flags = omap_formats[index].flags;
	strlcpy(fmt->description, omap_formats[index].description,
			sizeof(fmt->description));
	fmt->pixelformat = omap_formats[index].pixelformat;

	return 0;
}