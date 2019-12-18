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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct csis_pix_format {int /*<<< orphan*/  pix_width_alignment; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIS_MAX_PIX_HEIGHT ; 
 int /*<<< orphan*/  CSIS_MAX_PIX_WIDTH ; 
 struct csis_pix_format* find_csis_format (struct v4l2_mbus_framefmt*) ; 
 struct csis_pix_format* s5pcsis_formats ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct csis_pix_format const *s5pcsis_try_format(
	struct v4l2_mbus_framefmt *mf)
{
	struct csis_pix_format const *csis_fmt;

	csis_fmt = find_csis_format(mf);
	if (csis_fmt == NULL)
		csis_fmt = &s5pcsis_formats[0];

	mf->code = csis_fmt->code;
	v4l_bound_align_image(&mf->width, 1, CSIS_MAX_PIX_WIDTH,
			      csis_fmt->pix_width_alignment,
			      &mf->height, 1, CSIS_MAX_PIX_HEIGHT, 1,
			      0);
	return csis_fmt;
}