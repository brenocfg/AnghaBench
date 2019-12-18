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
struct vivid_dev {size_t num_outputs; int* output_type; int* output_name_counter; int /*<<< orphan*/  has_audio_outputs; } ;
struct v4l2_output {size_t index; int audioset; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  HDMI 129 
#define  SVID 128 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOG ; 
 int /*<<< orphan*/  V4L2_OUT_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  V4L2_OUT_CAP_STD ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_audio_outputs ; 

int vidioc_enum_output(struct file *file, void *priv,
				struct v4l2_output *out)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (out->index >= dev->num_outputs)
		return -EINVAL;

	out->type = V4L2_OUTPUT_TYPE_ANALOG;
	switch (dev->output_type[out->index]) {
	case SVID:
		snprintf(out->name, sizeof(out->name), "S-Video %u",
				dev->output_name_counter[out->index]);
		out->std = V4L2_STD_ALL;
		if (dev->has_audio_outputs)
			out->audioset = (1 << ARRAY_SIZE(vivid_audio_outputs)) - 1;
		out->capabilities = V4L2_OUT_CAP_STD;
		break;
	case HDMI:
		snprintf(out->name, sizeof(out->name), "HDMI %u",
				dev->output_name_counter[out->index]);
		out->capabilities = V4L2_OUT_CAP_DV_TIMINGS;
		break;
	}
	return 0;
}