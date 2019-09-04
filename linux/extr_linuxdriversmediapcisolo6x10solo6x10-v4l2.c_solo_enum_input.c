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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  status; int /*<<< orphan*/  name; } ;
struct solo_dev {scalar_t__ nr_chans; TYPE_1__* vfd; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int solo_enum_ext_input (struct solo_dev*,struct v4l2_input*) ; 
 int /*<<< orphan*/  tw28_get_video_status (struct solo_dev*,int) ; 
 struct solo_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_enum_input(struct file *file, void *priv,
			   struct v4l2_input *input)
{
	struct solo_dev *solo_dev = video_drvdata(file);

	if (input->index >= solo_dev->nr_chans) {
		int ret = solo_enum_ext_input(solo_dev, input);

		if (ret < 0)
			return ret;
	} else {
		snprintf(input->name, sizeof(input->name), "Camera %d",
			 input->index + 1);

		/* We can only check this for normal inputs */
		if (!tw28_get_video_status(solo_dev, input->index))
			input->status = V4L2_IN_ST_NO_SIGNAL;
	}

	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = solo_dev->vfd->tvnorms;
	return 0;
}