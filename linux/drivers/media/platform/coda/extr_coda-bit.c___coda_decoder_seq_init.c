#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int left; int top; int width; int height; } ;
struct coda_q_data {scalar_t__ fourcc; int bytesperline; int height; TYPE_1__ rect; } ;
struct coda_dev {TYPE_6__* devtype; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  coda_mutex; } ;
struct TYPE_11__ {int paddr; } ;
struct TYPE_10__ {scalar_t__ codec_mode_aux; int /*<<< orphan*/  codec_mode; } ;
struct TYPE_8__ {scalar_t__ paddr; scalar_t__ size; } ;
struct coda_ctx {int frame_mem_ctrl; scalar_t__ tiled_map_type; int display_idx; unsigned int sequence_offset; int initialized; int num_internal_frames; scalar_t__ use_vdoa; scalar_t__ bit_stream_param; TYPE_5__ psbuf; TYPE_4__ params; TYPE_3__* codec; int /*<<< orphan*/  reg_idx; scalar_t__ frm_dis_flg; TYPE_2__ bitstream; struct coda_dev* dev; } ;
struct TYPE_12__ {scalar_t__ product; } ;
struct TYPE_9__ {scalar_t__ src_fourcc; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ CODA7_PICHEIGHT_MASK ; 
 scalar_t__ CODA7_PICWIDTH_MASK ; 
 scalar_t__ CODA7_PICWIDTH_OFFSET ; 
 int CODA7_PS_BUF_SIZE ; 
 int /*<<< orphan*/  CODA7_RET_DEC_SEQ_HEADER_REPORT ; 
 int CODA9_FRAME_TILED2LINEAR ; 
 scalar_t__ CODADX6_PICHEIGHT_MASK ; 
 scalar_t__ CODADX6_PICWIDTH_MASK ; 
 scalar_t__ CODADX6_PICWIDTH_OFFSET ; 
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_BIT_DEC_SEQ_INIT_ESCAPE ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_BB_SIZE ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_BB_START ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_JPG_THUMB_EN ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_MP4_ASP_CLASS ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_OPTION ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_PS_BB_SIZE ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_PS_BB_START ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_SPP_CHUNK_SIZE ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_SRC_SIZE ; 
 int /*<<< orphan*/  CODA_CMD_DEC_SEQ_X264_MV_EN ; 
 int /*<<< orphan*/  CODA_COMMAND_SEQ_INIT ; 
 scalar_t__ CODA_DX6 ; 
 int CODA_FRAME_CHROMA_INTERLEAVE ; 
 scalar_t__ CODA_HX4 ; 
 int CODA_MAX_FRAMEBUFFERS ; 
 scalar_t__ CODA_MP4_AUX_MPEG4 ; 
 int CODA_MP4_CLASS_MPEG4 ; 
 scalar_t__ CODA_NO_INT_ENABLE ; 
 int /*<<< orphan*/  CODA_REG_BIT_FRAME_MEM_CTRL ; 
 int /*<<< orphan*/  CODA_REG_BIT_FRM_DIS_FLG (int /*<<< orphan*/ ) ; 
 scalar_t__ CODA_REORDER_ENABLE ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_CROP_LEFT_RIGHT ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_CROP_TOP_BOTTOM ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_ERR_REASON ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_FRAME_NEED ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_SRC_SIZE ; 
 int /*<<< orphan*/  CODA_RET_DEC_SEQ_SUCCESS ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ GDI_TILED_FRAME_MB_RASTER_MAP ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_MPEG4 ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int coda_command_sync (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_dbg (int,struct coda_ctx*,char*,...) ; 
 int /*<<< orphan*/  coda_kfifo_sync_from_device (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_kfifo_sync_to_device_full (struct coda_ctx*) ; 
 void* coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ coda_reorder_enable (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_update_profile_level_ctrls (struct coda_ctx*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,int,int /*<<< orphan*/ ) ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int __coda_decoder_seq_init(struct coda_ctx *ctx)
{
	struct coda_q_data *q_data_src, *q_data_dst;
	u32 bitstream_buf, bitstream_size;
	struct coda_dev *dev = ctx->dev;
	int width, height;
	u32 src_fourcc, dst_fourcc;
	u32 val;
	int ret;

	lockdep_assert_held(&dev->coda_mutex);

	coda_dbg(1, ctx, "Video Data Order Adapter: %s\n",
		 ctx->use_vdoa ? "Enabled" : "Disabled");

	/* Start decoding */
	q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_data_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	bitstream_buf = ctx->bitstream.paddr;
	bitstream_size = ctx->bitstream.size;
	src_fourcc = q_data_src->fourcc;
	dst_fourcc = q_data_dst->fourcc;

	/* Update coda bitstream read and write pointers from kfifo */
	coda_kfifo_sync_to_device_full(ctx);

	ctx->frame_mem_ctrl &= ~(CODA_FRAME_CHROMA_INTERLEAVE | (0x3 << 9) |
				 CODA9_FRAME_TILED2LINEAR);
	if (dst_fourcc == V4L2_PIX_FMT_NV12 || dst_fourcc == V4L2_PIX_FMT_YUYV)
		ctx->frame_mem_ctrl |= CODA_FRAME_CHROMA_INTERLEAVE;
	if (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		ctx->frame_mem_ctrl |= (0x3 << 9) |
			((ctx->use_vdoa) ? 0 : CODA9_FRAME_TILED2LINEAR);
	coda_write(dev, ctx->frame_mem_ctrl, CODA_REG_BIT_FRAME_MEM_CTRL);

	ctx->display_idx = -1;
	ctx->frm_dis_flg = 0;
	coda_write(dev, 0, CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));

	coda_write(dev, bitstream_buf, CODA_CMD_DEC_SEQ_BB_START);
	coda_write(dev, bitstream_size / 1024, CODA_CMD_DEC_SEQ_BB_SIZE);
	val = 0;
	if (coda_reorder_enable(ctx))
		val |= CODA_REORDER_ENABLE;
	if (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG)
		val |= CODA_NO_INT_ENABLE;
	coda_write(dev, val, CODA_CMD_DEC_SEQ_OPTION);

	ctx->params.codec_mode = ctx->codec->mode;
	if (dev->devtype->product == CODA_960 &&
	    src_fourcc == V4L2_PIX_FMT_MPEG4)
		ctx->params.codec_mode_aux = CODA_MP4_AUX_MPEG4;
	else
		ctx->params.codec_mode_aux = 0;
	if (src_fourcc == V4L2_PIX_FMT_MPEG4) {
		coda_write(dev, CODA_MP4_CLASS_MPEG4,
			   CODA_CMD_DEC_SEQ_MP4_ASP_CLASS);
	}
	if (src_fourcc == V4L2_PIX_FMT_H264) {
		if (dev->devtype->product == CODA_HX4 ||
		    dev->devtype->product == CODA_7541) {
			coda_write(dev, ctx->psbuf.paddr,
					CODA_CMD_DEC_SEQ_PS_BB_START);
			coda_write(dev, (CODA7_PS_BUF_SIZE / 1024),
					CODA_CMD_DEC_SEQ_PS_BB_SIZE);
		}
		if (dev->devtype->product == CODA_960) {
			coda_write(dev, 0, CODA_CMD_DEC_SEQ_X264_MV_EN);
			coda_write(dev, 512, CODA_CMD_DEC_SEQ_SPP_CHUNK_SIZE);
		}
	}
	if (src_fourcc == V4L2_PIX_FMT_JPEG)
		coda_write(dev, 0, CODA_CMD_DEC_SEQ_JPG_THUMB_EN);
	if (dev->devtype->product != CODA_960)
		coda_write(dev, 0, CODA_CMD_DEC_SEQ_SRC_SIZE);

	ctx->bit_stream_param = CODA_BIT_DEC_SEQ_INIT_ESCAPE;
	ret = coda_command_sync(ctx, CODA_COMMAND_SEQ_INIT);
	ctx->bit_stream_param = 0;
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "CODA_COMMAND_SEQ_INIT timeout\n");
		return ret;
	}
	ctx->sequence_offset = ~0U;
	ctx->initialized = 1;

	/* Update kfifo out pointer from coda bitstream read pointer */
	coda_kfifo_sync_from_device(ctx);

	if (coda_read(dev, CODA_RET_DEC_SEQ_SUCCESS) == 0) {
		v4l2_err(&dev->v4l2_dev,
			"CODA_COMMAND_SEQ_INIT failed, error code = 0x%x\n",
			coda_read(dev, CODA_RET_DEC_SEQ_ERR_REASON));
		return -EAGAIN;
	}

	val = coda_read(dev, CODA_RET_DEC_SEQ_SRC_SIZE);
	if (dev->devtype->product == CODA_DX6) {
		width = (val >> CODADX6_PICWIDTH_OFFSET) & CODADX6_PICWIDTH_MASK;
		height = val & CODADX6_PICHEIGHT_MASK;
	} else {
		width = (val >> CODA7_PICWIDTH_OFFSET) & CODA7_PICWIDTH_MASK;
		height = val & CODA7_PICHEIGHT_MASK;
	}

	if (width > q_data_dst->bytesperline || height > q_data_dst->height) {
		v4l2_err(&dev->v4l2_dev, "stream is %dx%d, not %dx%d\n",
			 width, height, q_data_dst->bytesperline,
			 q_data_dst->height);
		return -EINVAL;
	}

	width = round_up(width, 16);
	height = round_up(height, 16);

	coda_dbg(1, ctx, "start decoding: %dx%d\n", width, height);

	ctx->num_internal_frames = coda_read(dev, CODA_RET_DEC_SEQ_FRAME_NEED);
	/*
	 * If the VDOA is used, the decoder needs one additional frame,
	 * because the frames are freed when the next frame is decoded.
	 * Otherwise there are visible errors in the decoded frames (green
	 * regions in displayed frames) and a broken order of frames (earlier
	 * frames are sporadically displayed after later frames).
	 */
	if (ctx->use_vdoa)
		ctx->num_internal_frames += 1;
	if (ctx->num_internal_frames > CODA_MAX_FRAMEBUFFERS) {
		v4l2_err(&dev->v4l2_dev,
			 "not enough framebuffers to decode (%d < %d)\n",
			 CODA_MAX_FRAMEBUFFERS, ctx->num_internal_frames);
		return -EINVAL;
	}

	if (src_fourcc == V4L2_PIX_FMT_H264) {
		u32 left_right;
		u32 top_bottom;

		left_right = coda_read(dev, CODA_RET_DEC_SEQ_CROP_LEFT_RIGHT);
		top_bottom = coda_read(dev, CODA_RET_DEC_SEQ_CROP_TOP_BOTTOM);

		q_data_dst->rect.left = (left_right >> 10) & 0x3ff;
		q_data_dst->rect.top = (top_bottom >> 10) & 0x3ff;
		q_data_dst->rect.width = width - q_data_dst->rect.left -
					 (left_right & 0x3ff);
		q_data_dst->rect.height = height - q_data_dst->rect.top -
					  (top_bottom & 0x3ff);
	}

	if (dev->devtype->product != CODA_DX6) {
		u8 profile, level;

		val = coda_read(dev, CODA7_RET_DEC_SEQ_HEADER_REPORT);
		profile = val & 0xff;
		level = (val >> 8) & 0x7f;

		if (profile || level)
			coda_update_profile_level_ctrls(ctx, profile, level);
	}

	return 0;
}