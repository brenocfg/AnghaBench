#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_frmivalenum {scalar_t__ pixel_format; int index; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_8__ {scalar_t__ sensor_flags; } ;
struct TYPE_7__ {scalar_t__ device_type; } ;
struct TYPE_9__ {TYPE_2__ version; TYPE_1__ pnp_id; } ;
struct camera_data {TYPE_3__ params; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  period; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 scalar_t__ CPIA2_VP_SENSOR_FLAGS_500 ; 
 scalar_t__ DEVICE_STV_672 ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
 TYPE_4__* cpia2_framesizes ; 
 TYPE_4__* framerate_controls ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_enum_frameintervals(struct file *file, void *fh,
					   struct v4l2_frmivalenum *fival)
{
	struct camera_data *cam = video_drvdata(file);
	int max = ARRAY_SIZE(framerate_controls) - 1;
	int i;

	if (fival->pixel_format != V4L2_PIX_FMT_MJPEG &&
	    fival->pixel_format != V4L2_PIX_FMT_JPEG)
		return -EINVAL;

	/* Maximum 15 fps for this model */
	if (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
		max -= 2;
	if (fival->index > max)
		return -EINVAL;
	for (i = 0; i < ARRAY_SIZE(cpia2_framesizes); i++)
		if (fival->width == cpia2_framesizes[i].width &&
		    fival->height == cpia2_framesizes[i].height)
			break;
	if (i == ARRAY_SIZE(cpia2_framesizes))
		return -EINVAL;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = framerate_controls[fival->index].period;
	return 0;
}