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
struct vimc_deb_pix_map {int dummy; } ;
struct v4l2_mbus_framefmt {int width; int height; scalar_t__ field; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {scalar_t__ field; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_WIDTH ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_WIDTH ; 
 int clamp_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sink_fmt_default ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  vimc_colorimetry_clamp (struct v4l2_mbus_framefmt*) ; 
 struct vimc_deb_pix_map* vimc_deb_pix_map_by_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vimc_deb_adjust_sink_fmt(struct v4l2_mbus_framefmt *fmt)
{
	const struct vimc_deb_pix_map *vpix;

	/* Don't accept a code that is not on the debayer table */
	vpix = vimc_deb_pix_map_by_code(fmt->code);
	if (!vpix)
		fmt->code = sink_fmt_default.code;

	fmt->width = clamp_t(u32, fmt->width, VIMC_FRAME_MIN_WIDTH,
			     VIMC_FRAME_MAX_WIDTH) & ~1;
	fmt->height = clamp_t(u32, fmt->height, VIMC_FRAME_MIN_HEIGHT,
			      VIMC_FRAME_MAX_HEIGHT) & ~1;

	if (fmt->field == V4L2_FIELD_ANY)
		fmt->field = sink_fmt_default.field;

	vimc_colorimetry_clamp(fmt);
}