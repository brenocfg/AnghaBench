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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  index; } ;
struct mtk_mdp_fmt {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_mdp_fmt* mtk_mdp_find_fmt_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_enum_fmt(struct v4l2_fmtdesc *f, u32 type)
{
	const struct mtk_mdp_fmt *fmt;

	fmt = mtk_mdp_find_fmt_by_index(f->index, type);
	if (!fmt)
		return -EINVAL;

	f->pixelformat = fmt->pixelformat;

	return 0;
}