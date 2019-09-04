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
struct v4l2_fmtdesc {int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPE_FMT_TYPE_CAPTURE ; 
 int /*<<< orphan*/  VPE_FMT_TYPE_OUTPUT ; 
 int __enum_fmt (struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpe_enum_fmt(struct file *file, void *priv,
				struct v4l2_fmtdesc *f)
{
	if (V4L2_TYPE_IS_OUTPUT(f->type))
		return __enum_fmt(f, VPE_FMT_TYPE_OUTPUT);

	return __enum_fmt(f, VPE_FMT_TYPE_CAPTURE);
}