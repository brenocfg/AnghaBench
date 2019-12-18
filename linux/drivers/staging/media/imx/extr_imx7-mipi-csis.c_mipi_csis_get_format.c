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
struct csi_state {struct v4l2_mbus_framefmt format_mbus; int /*<<< orphan*/  mipi_sd; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
mipi_csis_get_format(struct csi_state *state,
		     struct v4l2_subdev_pad_config *cfg,
		     enum v4l2_subdev_format_whence which,
		     unsigned int pad)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_format(&state->mipi_sd, cfg, pad);

	return &state->format_mbus;
}