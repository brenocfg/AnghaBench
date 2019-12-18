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
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int mtk_mdp_enum_fmt (struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_m2m_enum_fmt_vid_out(struct file *file, void *priv,
					struct v4l2_fmtdesc *f)
{
	return mtk_mdp_enum_fmt(f, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
}