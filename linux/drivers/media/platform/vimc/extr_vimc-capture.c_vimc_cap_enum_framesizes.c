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
struct vimc_pix_map {int dummy; } ;
struct TYPE_2__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {TYPE_1__ stepwise; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MAX_WIDTH ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_HEIGHT ; 
 int /*<<< orphan*/  VIMC_FRAME_MIN_WIDTH ; 
 struct vimc_pix_map* vimc_pix_map_by_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vimc_cap_enum_framesizes(struct file *file, void *fh,
				    struct v4l2_frmsizeenum *fsize)
{
	const struct vimc_pix_map *vpix;

	if (fsize->index)
		return -EINVAL;

	/* Only accept code in the pix map table */
	vpix = vimc_pix_map_by_code(fsize->pixel_format);
	if (!vpix)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = VIMC_FRAME_MIN_WIDTH;
	fsize->stepwise.max_width = VIMC_FRAME_MAX_WIDTH;
	fsize->stepwise.min_height = VIMC_FRAME_MIN_HEIGHT;
	fsize->stepwise.max_height = VIMC_FRAME_MAX_HEIGHT;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	return 0;
}