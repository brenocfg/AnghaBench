#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_8__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_9__ {TYPE_1__ time_per_frame; } ;
struct TYPE_10__ {int error; } ;
struct hva_ctx {TYPE_2__ ctrls; TYPE_3__ ctrl_handler; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  enum v4l2_mpeg_video_h264_sei_fp_arrangement_type { ____Placeholder_v4l2_mpeg_video_h264_sei_fp_arrangement_type } v4l2_mpeg_video_h264_sei_fp_arrangement_type ;

/* Variables and functions */
 int /*<<< orphan*/  HVA_DEFAULT_FRAME_DEN ; 
 int /*<<< orphan*/  HVA_DEFAULT_FRAME_NUM ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_ASPECT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MAX_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MIN_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC ; 
 int V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC ; 
 int V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_2 ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_TOP_BOTTOM ; 
 int V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1 ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hva_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int hva_ctrls_setup(struct hva_ctx *ctx)
{
	struct device *dev = ctx_to_dev(ctx);
	u64 mask;
	enum v4l2_mpeg_video_h264_sei_fp_arrangement_type sei_fp_type =
		V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_TOP_BOTTOM;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 15);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
			       0,
			       V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			  1, 60, 1, 16);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_BITRATE,
			  1000, 60000000, 1000, 20000000);

	mask = ~(1 << V4L2_MPEG_VIDEO_ASPECT_1x1);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_ASPECT,
			       V4L2_MPEG_VIDEO_ASPECT_1x1,
			       mask,
			       V4L2_MPEG_VIDEO_ASPECT_1x1);

	mask = ~((1 << V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MAIN) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROFILE_HIGH) |
		 (1 << V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH));
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_PROFILE,
			       V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH,
			       mask,
			       V4L2_MPEG_VIDEO_H264_PROFILE_HIGH);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			       V4L2_MPEG_VIDEO_H264_LEVEL_4_2,
			       0,
			       V4L2_MPEG_VIDEO_H264_LEVEL_4_0);

	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
			       V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC,
			       0,
			       V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE,
			  1, 10000, 1, 3000);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM,
			  0, 1, 1, 0);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MIN_QP,
			  0, 51, 1, 5);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MAX_QP,
			  0, 51, 1, 51);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE,
			  0, 1, 1, 1);

	mask = ~(1 << V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC,
			       V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1,
			       mask,
			       V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1);

	v4l2_ctrl_new_std(&ctx->ctrl_handler, &hva_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING,
			  0, 1, 1, 0);

	mask = ~(1 << sei_fp_type);
	v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &hva_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE,
			       sei_fp_type,
			       mask,
			       sei_fp_type);

	if (ctx->ctrl_handler.error) {
		int err = ctx->ctrl_handler.error;

		dev_dbg(dev, "%s controls setup failed (%d)\n",
			ctx->name, err);
		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		return err;
	}

	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	/* set default time per frame */
	ctx->ctrls.time_per_frame.numerator = HVA_DEFAULT_FRAME_NUM;
	ctx->ctrls.time_per_frame.denominator = HVA_DEFAULT_FRAME_DEN;

	return 0;
}