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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int imx_media_enum_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_csc_scaler_enum_fmt(struct file *file, void *fh,
				   struct v4l2_fmtdesc *f)
{
	u32 fourcc;
	int ret;

	ret = imx_media_enum_format(&fourcc, f->index, CS_SEL_ANY);
	if (ret)
		return ret;

	f->pixelformat = fourcc;

	return 0;
}