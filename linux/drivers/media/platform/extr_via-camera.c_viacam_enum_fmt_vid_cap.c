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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t N_VIA_FMTS ; 
 TYPE_1__* via_formats ; 

__attribute__((used)) static int viacam_enum_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_fmtdesc *fmt)
{
	if (fmt->index >= N_VIA_FMTS)
		return -EINVAL;
	fmt->pixelformat = via_formats[fmt->index].pixelformat;
	return 0;
}