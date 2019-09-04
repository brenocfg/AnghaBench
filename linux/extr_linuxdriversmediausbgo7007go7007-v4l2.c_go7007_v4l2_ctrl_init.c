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
struct v4l2_ctrl_handler {int error; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct go7007 {TYPE_1__ v4l2_dev; void* modet_mode; void* mpeg_video_aspect_ratio; void* mpeg_video_rep_seqheader; void* mpeg_video_b_frames; void* mpeg_video_bitrate; void* mpeg_video_gop_closure; void* mpeg_video_gop_size; struct v4l2_ctrl_handler hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_DETECT_MD_MODE ; 
 int /*<<< orphan*/  V4L2_CID_JPEG_ACTIVE_MARKER ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_ASPECT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_B_FRAMES ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  V4L2_DETECT_MD_MODE_DISABLED ; 
 int /*<<< orphan*/  V4L2_DETECT_MD_MODE_REGION_GRID ; 
 int V4L2_DETECT_MD_MODE_THRESHOLD_GRID ; 
 int V4L2_JPEG_ACTIVE_MARKER_DHT ; 
 int V4L2_JPEG_ACTIVE_MARKER_DQT ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ASPECT_16x9 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int /*<<< orphan*/  go7007_mb_regions_ctrl ; 
 int /*<<< orphan*/  go7007_mb_threshold0_ctrl ; 
 int /*<<< orphan*/  go7007_mb_threshold1_ctrl ; 
 int /*<<< orphan*/  go7007_mb_threshold2_ctrl ; 
 int /*<<< orphan*/  go7007_mb_threshold3_ctrl ; 
 int /*<<< orphan*/  go7007_motion_threshold0_ctrl ; 
 int /*<<< orphan*/  go7007_motion_threshold1_ctrl ; 
 int /*<<< orphan*/  go7007_motion_threshold2_ctrl ; 
 int /*<<< orphan*/  go7007_motion_threshold3_ctrl ; 
 int /*<<< orphan*/  go7007_pixel_threshold0_ctrl ; 
 int /*<<< orphan*/  go7007_pixel_threshold1_ctrl ; 
 int /*<<< orphan*/  go7007_pixel_threshold2_ctrl ; 
 int /*<<< orphan*/  go7007_pixel_threshold3_ctrl ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 

int go7007_v4l2_ctrl_init(struct go7007 *go)
{
	struct v4l2_ctrl_handler *hdl = &go->hdl;
	struct v4l2_ctrl *ctrl;

	v4l2_ctrl_handler_init(hdl, 22);
	go->mpeg_video_gop_size = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, 34, 1, 15);
	go->mpeg_video_gop_closure = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_GOP_CLOSURE, 0, 1, 1, 1);
	go->mpeg_video_bitrate = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_BITRATE,
			64000, 10000000, 1, 9800000);
	go->mpeg_video_b_frames = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_B_FRAMES, 0, 2, 2, 0);
	go->mpeg_video_rep_seqheader = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER, 0, 1, 1, 1);

	go->mpeg_video_aspect_ratio = v4l2_ctrl_new_std_menu(hdl, NULL,
			V4L2_CID_MPEG_VIDEO_ASPECT,
			V4L2_MPEG_VIDEO_ASPECT_16x9, 0,
			V4L2_MPEG_VIDEO_ASPECT_1x1);
	ctrl = v4l2_ctrl_new_std(hdl, NULL,
			V4L2_CID_JPEG_ACTIVE_MARKER, 0,
			V4L2_JPEG_ACTIVE_MARKER_DQT |
			V4L2_JPEG_ACTIVE_MARKER_DHT, 0,
			V4L2_JPEG_ACTIVE_MARKER_DQT |
			V4L2_JPEG_ACTIVE_MARKER_DHT);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold0_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold0_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold0_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold1_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold1_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold1_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold2_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold2_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold2_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold3_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold3_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold3_ctrl, NULL);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_regions_ctrl, NULL);
	go->modet_mode = v4l2_ctrl_new_std_menu(hdl, NULL,
			V4L2_CID_DETECT_MD_MODE,
			V4L2_DETECT_MD_MODE_REGION_GRID,
			1 << V4L2_DETECT_MD_MODE_THRESHOLD_GRID,
			V4L2_DETECT_MD_MODE_DISABLED);
	if (hdl->error) {
		int rv = hdl->error;

		v4l2_err(&go->v4l2_dev, "Could not register controls\n");
		return rv;
	}
	go->v4l2_dev.ctrl_handler = hdl;
	return 0;
}