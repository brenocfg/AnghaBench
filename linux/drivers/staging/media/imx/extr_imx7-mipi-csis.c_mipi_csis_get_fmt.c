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
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct csi_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct v4l2_mbus_framefmt* mipi_csis_get_format (struct csi_state*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipi_csis_get_fmt(struct v4l2_subdev *mipi_sd,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_format *sdformat)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	struct v4l2_mbus_framefmt *fmt;

	mutex_lock(&state->lock);

	fmt = mipi_csis_get_format(state, cfg, sdformat->which, sdformat->pad);

	sdformat->format = *fmt;

	mutex_unlock(&state->lock);

	return 0;
}