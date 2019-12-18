#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5K5BAF_CIS_HEIGHT ; 
 int /*<<< orphan*/  S5K5BAF_CIS_WIDTH ; 
 int /*<<< orphan*/  S5K5BAF_WIN_HEIGHT_MIN ; 
 int /*<<< orphan*/  S5K5BAF_WIN_WIDTH_MIN ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int s5k5baf_find_pixfmt (struct v4l2_mbus_framefmt*) ; 
 TYPE_1__* s5k5baf_formats ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k5baf_try_isp_format(struct v4l2_mbus_framefmt *mf)
{
	int pixfmt;

	v4l_bound_align_image(&mf->width, S5K5BAF_WIN_WIDTH_MIN,
			      S5K5BAF_CIS_WIDTH, 1,
			      &mf->height, S5K5BAF_WIN_HEIGHT_MIN,
			      S5K5BAF_CIS_HEIGHT, 1, 0);

	pixfmt = s5k5baf_find_pixfmt(mf);

	mf->colorspace = s5k5baf_formats[pixfmt].colorspace;
	mf->code = s5k5baf_formats[pixfmt].code;
	mf->field = V4L2_FIELD_NONE;

	return pixfmt;
}