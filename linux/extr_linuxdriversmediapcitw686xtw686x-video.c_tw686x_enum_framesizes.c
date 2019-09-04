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
struct TYPE_2__ {int max_width; int min_width; int step_width; int max_height; int min_height; int step_height; } ;
struct v4l2_frmsizeenum {TYPE_1__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct tw686x_video_channel {int /*<<< orphan*/  video_standard; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TW686X_VIDEO_HEIGHT (int /*<<< orphan*/ ) ; 
 int TW686X_VIDEO_WIDTH ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
 struct tw686x_video_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw686x_enum_framesizes(struct file *file, void *priv,
				  struct v4l2_frmsizeenum *fsize)
{
	struct tw686x_video_channel *vc = video_drvdata(file);

	if (fsize->index)
		return -EINVAL;
	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.max_width = TW686X_VIDEO_WIDTH;
	fsize->stepwise.min_width = fsize->stepwise.max_width / 2;
	fsize->stepwise.step_width = fsize->stepwise.min_width;
	fsize->stepwise.max_height = TW686X_VIDEO_HEIGHT(vc->video_standard);
	fsize->stepwise.min_height = fsize->stepwise.max_height / 2;
	fsize->stepwise.step_height = fsize->stepwise.min_height;
	return 0;
}