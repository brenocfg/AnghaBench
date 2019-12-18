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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_JPEG_FMT_FLAG_DEC_OUTPUT ; 
 int /*<<< orphan*/  MTK_JPEG_NUM_FORMATS ; 
 int mtk_jpeg_enum_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_formats ; 

__attribute__((used)) static int mtk_jpeg_enum_fmt_vid_out(struct file *file, void *priv,
				     struct v4l2_fmtdesc *f)
{
	return mtk_jpeg_enum_fmt(mtk_jpeg_formats, MTK_JPEG_NUM_FORMATS, f,
				 MTK_JPEG_FMT_FLAG_DEC_OUTPUT);
}