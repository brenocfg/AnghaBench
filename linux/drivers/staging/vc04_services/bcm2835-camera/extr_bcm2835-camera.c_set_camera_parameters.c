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
struct vchiq_mmal_instance {int dummy; } ;
struct vchiq_mmal_component {int /*<<< orphan*/  control; } ;
struct mmal_parameter_camera_config {int stills_yuv422; int one_shot_stills; int max_preview_video_w; int max_preview_video_h; int num_preview_video_frames; int /*<<< orphan*/  use_stc_timestamp; int /*<<< orphan*/  fast_preview_resume; int /*<<< orphan*/  stills_capture_circular_buffer_height; int /*<<< orphan*/  max_stills_h; int /*<<< orphan*/  max_stills_w; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
typedef  int /*<<< orphan*/  cam_config ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_CONFIG ; 
 int /*<<< orphan*/  MMAL_PARAM_TIMESTAMP_MODE_RAW_STC ; 
 int max_video_height ; 
 int max_video_width ; 
 int vchiq_mmal_port_parameter_set (struct vchiq_mmal_instance*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mmal_parameter_camera_config*,int) ; 

__attribute__((used)) static int set_camera_parameters(struct vchiq_mmal_instance *instance,
				 struct vchiq_mmal_component *camera,
				 struct bm2835_mmal_dev *dev)
{
	struct mmal_parameter_camera_config cam_config = {
		.max_stills_w = dev->max_width,
		.max_stills_h = dev->max_height,
		.stills_yuv422 = 1,
		.one_shot_stills = 1,
		.max_preview_video_w = (max_video_width > 1920) ?
						max_video_width : 1920,
		.max_preview_video_h = (max_video_height > 1088) ?
						max_video_height : 1088,
		.num_preview_video_frames = 3,
		.stills_capture_circular_buffer_height = 0,
		.fast_preview_resume = 0,
		.use_stc_timestamp = MMAL_PARAM_TIMESTAMP_MODE_RAW_STC
	};

	return vchiq_mmal_port_parameter_set(instance, &camera->control,
					    MMAL_PARAMETER_CAMERA_CONFIG,
					    &cam_config, sizeof(cam_config));
}