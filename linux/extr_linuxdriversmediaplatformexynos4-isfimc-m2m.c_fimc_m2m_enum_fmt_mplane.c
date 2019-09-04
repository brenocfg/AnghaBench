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
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
struct fimc_fmt {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fimc_fmt* fimc_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_m2m_fmt_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fimc_m2m_enum_fmt_mplane(struct file *file, void *priv,
				    struct v4l2_fmtdesc *f)
{
	struct fimc_fmt *fmt;

	fmt = fimc_find_format(NULL, NULL, get_m2m_fmt_flags(f->type),
			       f->index);
	if (!fmt)
		return -EINVAL;

	strncpy(f->description, fmt->name, sizeof(f->description) - 1);
	f->pixelformat = fmt->fourcc;
	return 0;
}