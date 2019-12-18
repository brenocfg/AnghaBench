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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct ceu_fmt {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct ceu_fmt*) ; 
 int EINVAL ; 
 struct ceu_fmt* ceu_fmt_list ; 

__attribute__((used)) static int ceu_enum_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_fmtdesc *f)
{
	const struct ceu_fmt *fmt;

	if (f->index >= ARRAY_SIZE(ceu_fmt_list))
		return -EINVAL;

	fmt = &ceu_fmt_list[f->index];
	f->pixelformat = fmt->fourcc;

	return 0;
}