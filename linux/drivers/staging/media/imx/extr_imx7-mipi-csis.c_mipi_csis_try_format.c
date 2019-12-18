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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct csis_pix_format {int /*<<< orphan*/  code; int /*<<< orphan*/  pix_width_alignment; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct csi_state {TYPE_1__ format_mbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIS_MAX_PIX_HEIGHT ; 
 int /*<<< orphan*/  CSIS_MAX_PIX_WIDTH ; 
 struct csis_pix_format* find_csis_format (int /*<<< orphan*/ ) ; 
 struct csis_pix_format* mipi_csis_formats ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct csis_pix_format const *
mipi_csis_try_format(struct v4l2_subdev *mipi_sd, struct v4l2_mbus_framefmt *mf)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	struct csis_pix_format const *csis_fmt;

	csis_fmt = find_csis_format(mf->code);
	if (!csis_fmt)
		csis_fmt = &mipi_csis_formats[0];

	v4l_bound_align_image(&mf->width, 1, CSIS_MAX_PIX_WIDTH,
			      csis_fmt->pix_width_alignment,
			      &mf->height, 1, CSIS_MAX_PIX_HEIGHT, 1,
			      0);

	state->format_mbus.code = csis_fmt->code;
	state->format_mbus.width = mf->width;
	state->format_mbus.height = mf->height;

	return csis_fmt;
}