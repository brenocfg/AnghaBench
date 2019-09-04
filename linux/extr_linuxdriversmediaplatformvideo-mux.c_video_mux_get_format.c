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
struct video_mux {int /*<<< orphan*/  lock; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __video_mux_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct video_mux* v4l2_subdev_to_video_mux (struct v4l2_subdev*) ; 

__attribute__((used)) static int video_mux_get_format(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *sdformat)
{
	struct video_mux *vmux = v4l2_subdev_to_video_mux(sd);

	mutex_lock(&vmux->lock);

	sdformat->format = *__video_mux_get_pad_format(sd, cfg, sdformat->pad,
						       sdformat->which);

	mutex_unlock(&vmux->lock);

	return 0;
}