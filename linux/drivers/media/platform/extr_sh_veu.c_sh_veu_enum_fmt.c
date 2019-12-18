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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* sh_veu_fmt ; 

__attribute__((used)) static int sh_veu_enum_fmt(struct v4l2_fmtdesc *f, const int *fmt, int fmt_num)
{
	if (f->index >= fmt_num)
		return -EINVAL;

	f->pixelformat = sh_veu_fmt[fmt[f->index]].fourcc;
	return 0;
}