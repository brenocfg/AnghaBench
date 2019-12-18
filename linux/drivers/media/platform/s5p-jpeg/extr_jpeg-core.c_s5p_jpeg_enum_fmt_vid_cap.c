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
struct v4l2_fmtdesc {int dummy; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ S5P_JPEG_ENCODE ; 
 int /*<<< orphan*/  SJPEG_FMT_FLAG_DEC_CAPTURE ; 
 int /*<<< orphan*/  SJPEG_FMT_FLAG_ENC_CAPTURE ; 
 int /*<<< orphan*/  SJPEG_NUM_FORMATS ; 
 int enum_fmt (struct s5p_jpeg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 
 struct s5p_jpeg_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  sjpeg_formats ; 

__attribute__((used)) static int s5p_jpeg_enum_fmt_vid_cap(struct file *file, void *priv,
				   struct v4l2_fmtdesc *f)
{
	struct s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	if (ctx->mode == S5P_JPEG_ENCODE)
		return enum_fmt(ctx, sjpeg_formats, SJPEG_NUM_FORMATS, f,
				SJPEG_FMT_FLAG_ENC_CAPTURE);

	return enum_fmt(ctx, sjpeg_formats, SJPEG_NUM_FORMATS, f,
			SJPEG_FMT_FLAG_DEC_CAPTURE);
}