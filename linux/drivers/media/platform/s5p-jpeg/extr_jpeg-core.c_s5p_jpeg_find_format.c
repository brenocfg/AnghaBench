#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct s5p_jpeg_fmt {scalar_t__ fourcc; unsigned int flags; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; TYPE_2__* jpeg; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {int fmt_ver_flag; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct s5p_jpeg_fmt*) ; 
 unsigned int FMT_TYPE_OUTPUT ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 unsigned int SJPEG_FMT_FLAG_DEC_CAPTURE ; 
 unsigned int SJPEG_FMT_FLAG_DEC_OUTPUT ; 
 unsigned int SJPEG_FMT_FLAG_ENC_CAPTURE ; 
 unsigned int SJPEG_FMT_FLAG_ENC_OUTPUT ; 
 struct s5p_jpeg_fmt* sjpeg_formats ; 

__attribute__((used)) static struct s5p_jpeg_fmt *s5p_jpeg_find_format(struct s5p_jpeg_ctx *ctx,
				u32 pixelformat, unsigned int fmt_type)
{
	unsigned int k, fmt_flag;

	if (ctx->mode == S5P_JPEG_ENCODE)
		fmt_flag = (fmt_type == FMT_TYPE_OUTPUT) ?
				SJPEG_FMT_FLAG_ENC_OUTPUT :
				SJPEG_FMT_FLAG_ENC_CAPTURE;
	else
		fmt_flag = (fmt_type == FMT_TYPE_OUTPUT) ?
				SJPEG_FMT_FLAG_DEC_OUTPUT :
				SJPEG_FMT_FLAG_DEC_CAPTURE;

	for (k = 0; k < ARRAY_SIZE(sjpeg_formats); k++) {
		struct s5p_jpeg_fmt *fmt = &sjpeg_formats[k];

		if (fmt->fourcc == pixelformat &&
		    fmt->flags & fmt_flag &&
		    fmt->flags & ctx->jpeg->variant->fmt_ver_flag) {
			return fmt;
		}
	}

	return NULL;
}