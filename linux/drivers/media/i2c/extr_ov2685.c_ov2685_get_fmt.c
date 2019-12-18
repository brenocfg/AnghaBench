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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct ov2685 {int /*<<< orphan*/  cur_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov2685_fill_fmt (int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 struct ov2685* to_ov2685 (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2685_get_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct ov2685 *ov2685 = to_ov2685(sd);
	struct v4l2_mbus_framefmt *mbus_fmt = &fmt->format;

	ov2685_fill_fmt(ov2685->cur_mode, mbus_fmt);

	return 0;
}