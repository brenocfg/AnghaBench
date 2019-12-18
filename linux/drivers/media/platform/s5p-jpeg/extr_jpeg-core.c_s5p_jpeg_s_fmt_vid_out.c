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
 int /*<<< orphan*/  fh_to_ctx (void*) ; 
 int s5p_jpeg_s_fmt (int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int s5p_jpeg_try_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int s5p_jpeg_s_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *f)
{
	int ret;

	ret = s5p_jpeg_try_fmt_vid_out(file, priv, f);
	if (ret)
		return ret;

	return s5p_jpeg_s_fmt(fh_to_ctx(priv), f);
}