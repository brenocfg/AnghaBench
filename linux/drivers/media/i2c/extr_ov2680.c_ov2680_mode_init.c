#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ov2680_mode_info {int dummy; } ;
struct TYPE_3__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct ov2680_dev {int mode_pending_changes; struct ov2680_mode_info const* current_mode; TYPE_1__ frame_interval; TYPE_2__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 int /*<<< orphan*/  OV2680_FRAME_RATE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct ov2680_mode_info ov2680_mode_init_data ; 

__attribute__((used)) static int ov2680_mode_init(struct ov2680_dev *sensor)
{
	const struct ov2680_mode_info *init_mode;

	/* set initial mode */
	sensor->fmt.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	sensor->fmt.width = 800;
	sensor->fmt.height = 600;
	sensor->fmt.field = V4L2_FIELD_NONE;
	sensor->fmt.colorspace = V4L2_COLORSPACE_SRGB;

	sensor->frame_interval.denominator = OV2680_FRAME_RATE;
	sensor->frame_interval.numerator = 1;

	init_mode = &ov2680_mode_init_data;

	sensor->current_mode = init_mode;

	sensor->mode_pending_changes = true;

	return 0;
}