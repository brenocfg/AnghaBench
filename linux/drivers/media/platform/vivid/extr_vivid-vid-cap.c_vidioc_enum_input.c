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
struct vivid_dev {size_t num_inputs; int* input_type; int* input_name_counter; scalar_t__* dv_timings_signal_mode; size_t input; scalar_t__* std_signal_mode; int /*<<< orphan*/  tpg; scalar_t__ sensor_vflip; scalar_t__ sensor_hflip; int /*<<< orphan*/  edid_blocks; int /*<<< orphan*/  has_audio_inputs; } ;
struct v4l2_input {size_t index; int audioset; int /*<<< orphan*/  status; void* capabilities; int /*<<< orphan*/  name; void* std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  HDMI 133 
 scalar_t__ NO_LOCK ; 
 scalar_t__ NO_SIGNAL ; 
 scalar_t__ OUT_OF_RANGE ; 
#define  SVID 132 
#define  TPG_QUAL_GRAY 131 
#define  TPG_QUAL_NOISE 130 
#define  TV 129 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 void* V4L2_IN_CAP_DV_TIMINGS ; 
 void* V4L2_IN_CAP_STD ; 
 int /*<<< orphan*/  V4L2_IN_ST_COLOR_KILL ; 
 int /*<<< orphan*/  V4L2_IN_ST_HFLIP ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/  V4L2_IN_ST_VFLIP ; 
 void* V4L2_STD_ALL ; 
#define  WEBCAM 128 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int tpg_g_quality (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_audio_inputs ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_tv_cap (struct vivid_dev*) ; 

int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *inp)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (inp->index >= dev->num_inputs)
		return -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	switch (dev->input_type[inp->index]) {
	case WEBCAM:
		snprintf(inp->name, sizeof(inp->name), "Webcam %u",
				dev->input_name_counter[inp->index]);
		inp->capabilities = 0;
		break;
	case TV:
		snprintf(inp->name, sizeof(inp->name), "TV %u",
				dev->input_name_counter[inp->index]);
		inp->type = V4L2_INPUT_TYPE_TUNER;
		inp->std = V4L2_STD_ALL;
		if (dev->has_audio_inputs)
			inp->audioset = (1 << ARRAY_SIZE(vivid_audio_inputs)) - 1;
		inp->capabilities = V4L2_IN_CAP_STD;
		break;
	case SVID:
		snprintf(inp->name, sizeof(inp->name), "S-Video %u",
				dev->input_name_counter[inp->index]);
		inp->std = V4L2_STD_ALL;
		if (dev->has_audio_inputs)
			inp->audioset = (1 << ARRAY_SIZE(vivid_audio_inputs)) - 1;
		inp->capabilities = V4L2_IN_CAP_STD;
		break;
	case HDMI:
		snprintf(inp->name, sizeof(inp->name), "HDMI %u",
				dev->input_name_counter[inp->index]);
		inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
		if (dev->edid_blocks == 0 ||
		    dev->dv_timings_signal_mode[dev->input] == NO_SIGNAL)
			inp->status |= V4L2_IN_ST_NO_SIGNAL;
		else if (dev->dv_timings_signal_mode[dev->input] == NO_LOCK ||
			 dev->dv_timings_signal_mode[dev->input] == OUT_OF_RANGE)
			inp->status |= V4L2_IN_ST_NO_H_LOCK;
		break;
	}
	if (dev->sensor_hflip)
		inp->status |= V4L2_IN_ST_HFLIP;
	if (dev->sensor_vflip)
		inp->status |= V4L2_IN_ST_VFLIP;
	if (dev->input == inp->index && vivid_is_sdtv_cap(dev)) {
		if (dev->std_signal_mode[dev->input] == NO_SIGNAL) {
			inp->status |= V4L2_IN_ST_NO_SIGNAL;
		} else if (dev->std_signal_mode[dev->input] == NO_LOCK) {
			inp->status |= V4L2_IN_ST_NO_H_LOCK;
		} else if (vivid_is_tv_cap(dev)) {
			switch (tpg_g_quality(&dev->tpg)) {
			case TPG_QUAL_GRAY:
				inp->status |= V4L2_IN_ST_COLOR_KILL;
				break;
			case TPG_QUAL_NOISE:
				inp->status |= V4L2_IN_ST_NO_H_LOCK;
				break;
			default:
				break;
			}
		}
	}
	return 0;
}