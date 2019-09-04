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
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int stk_try_fmt_vid_cap (struct file*,struct v4l2_format*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stk_vidioc_try_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_format *fmtd)
{
	return stk_try_fmt_vid_cap(filp, fmtd, NULL);
}