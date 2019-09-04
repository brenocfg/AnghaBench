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
struct gsc_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct gsc_ctx* fh_to_ctx (void*) ; 
 int gsc_g_fmt_mplane (struct gsc_ctx*,struct v4l2_format*) ; 

__attribute__((used)) static int gsc_m2m_g_fmt_mplane(struct file *file, void *fh,
			     struct v4l2_format *f)
{
	struct gsc_ctx *ctx = fh_to_ctx(fh);

	return gsc_g_fmt_mplane(ctx, f);
}