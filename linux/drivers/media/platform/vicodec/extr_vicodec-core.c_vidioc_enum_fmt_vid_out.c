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
struct vicodec_ctx {int dummy; } ;
struct v4l2_fmtdesc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int enum_fmt (struct v4l2_fmtdesc*,struct vicodec_ctx*,int) ; 
 struct vicodec_ctx* file2ctx (struct file*) ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_out(struct file *file, void *priv,
				   struct v4l2_fmtdesc *f)
{
	struct vicodec_ctx *ctx = file2ctx(file);

	return enum_fmt(f, ctx, true);
}