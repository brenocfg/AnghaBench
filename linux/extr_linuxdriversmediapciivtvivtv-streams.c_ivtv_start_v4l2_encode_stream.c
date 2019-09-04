#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct ivtv_stream {int type; int subtype; int /*<<< orphan*/  s_flags; scalar_t__ buffers_stolen; int /*<<< orphan*/  name; TYPE_1__ vdev; struct ivtv* itv; } ;
struct TYPE_9__ {int /*<<< orphan*/  video_mute_yuv; int /*<<< orphan*/  audio_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  sliced_mpeg_size; int /*<<< orphan*/  inserted_frame; int /*<<< orphan*/  frame; } ;
struct ivtv {int dualwatch_stereo_mode; int v4l2_cap; int /*<<< orphan*/  capturing; int /*<<< orphan*/  sd_video; int /*<<< orphan*/  sd_audio; TYPE_4__ cxhdl; int /*<<< orphan*/  i_flags; scalar_t__ has_cx23415; void* pgm_info_num; void* pgm_info_offset; scalar_t__ pgm_info_read_idx; scalar_t__ pgm_info_write_idx; TYPE_3__* card; TYPE_2__ vbi; int /*<<< orphan*/  output_mode; int /*<<< orphan*/  search_pack_header; int /*<<< orphan*/  dualwatch_jiffies; int /*<<< orphan*/  vbi_data_inserted; int /*<<< orphan*/  mpg_data_received; } ;
struct TYPE_8__ {int hw_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_INITIALIZE_INPUT ; 
 int /*<<< orphan*/  CX2341X_ENC_MISC ; 
 int /*<<< orphan*/  CX2341X_ENC_MUTE_VIDEO ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_DMA_BLOCK_SIZE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_EVENT_NOTIFICATION ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_NUM_VSYNC_LINES ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_PGM_INDEX_INFO ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_PLACEHOLDER ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_VERT_CROP_LINE ; 
 int /*<<< orphan*/  CX2341X_ENC_START_CAPTURE ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,void*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
#define  IVTV_ENC_STREAM_TYPE_MPG 131 
#define  IVTV_ENC_STREAM_TYPE_PCM 130 
#define  IVTV_ENC_STREAM_TYPE_VBI 129 
#define  IVTV_ENC_STREAM_TYPE_YUV 128 
 int /*<<< orphan*/  IVTV_F_I_DIG_RST ; 
 int /*<<< orphan*/  IVTV_F_I_EOS ; 
 int /*<<< orphan*/  IVTV_F_I_RADIO_USER ; 
 int /*<<< orphan*/  IVTV_F_S_STREAMOFF ; 
 int IVTV_HW_SAA7114 ; 
 int IVTV_HW_SAA7115 ; 
 int IVTV_HW_SAA717X ; 
 int /*<<< orphan*/  IVTV_IRQ_ENC_VBI_CAP ; 
 int /*<<< orphan*/  IVTV_IRQ_ENC_VIM_RST ; 
 int /*<<< orphan*/  IVTV_IRQ_MASK_CAPTURE ; 
 int /*<<< orphan*/  OUT_PASSTHROUGH ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx2341x_handler_set_busy (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cx2341x_handler_setup (TYPE_4__*) ; 
 int /*<<< orphan*/  ivtv_clear_irq_mask (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_passthrough_mode (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_set_irq_mask (struct ivtv*,int /*<<< orphan*/ ) ; 
 scalar_t__ ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ivtv_vapi_result (struct ivtv*,void**,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ivtv_vbi_setup (struct ivtv*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

int ivtv_start_v4l2_encode_stream(struct ivtv_stream *s)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	struct ivtv *itv = s->itv;
	int captype = 0, subtype = 0;
	int enable_passthrough = 0;

	if (s->vdev.v4l2_dev == NULL)
		return -EINVAL;

	IVTV_DEBUG_INFO("Start encoder stream %s\n", s->name);

	switch (s->type) {
	case IVTV_ENC_STREAM_TYPE_MPG:
		captype = 0;
		subtype = 3;

		/* Stop Passthrough */
		if (itv->output_mode == OUT_PASSTHROUGH) {
			ivtv_passthrough_mode(itv, 0);
			enable_passthrough = 1;
		}
		itv->mpg_data_received = itv->vbi_data_inserted = 0;
		itv->dualwatch_jiffies = jiffies;
		itv->dualwatch_stereo_mode = v4l2_ctrl_g_ctrl(itv->cxhdl.audio_mode);
		itv->search_pack_header = 0;
		break;

	case IVTV_ENC_STREAM_TYPE_YUV:
		if (itv->output_mode == OUT_PASSTHROUGH) {
			captype = 2;
			subtype = 11;	/* video+audio+decoder */
			break;
		}
		captype = 1;
		subtype = 1;
		break;
	case IVTV_ENC_STREAM_TYPE_PCM:
		captype = 1;
		subtype = 2;
		break;
	case IVTV_ENC_STREAM_TYPE_VBI:
		captype = 1;
		subtype = 4;

		itv->vbi.frame = 0;
		itv->vbi.inserted_frame = 0;
		memset(itv->vbi.sliced_mpeg_size,
			0, sizeof(itv->vbi.sliced_mpeg_size));
		break;
	default:
		return -EINVAL;
	}
	s->subtype = subtype;
	s->buffers_stolen = 0;

	/* Clear Streamoff flags in case left from last capture */
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	if (atomic_read(&itv->capturing) == 0) {
		int digitizer;

		/* Always use frame based mode. Experiments have demonstrated that byte
		   stream based mode results in dropped frames and corruption. Not often,
		   but occasionally. Many thanks go to Leonard Orb who spent a lot of
		   effort and time trying to trace the cause of the drop outs. */
		/* 1 frame per DMA */
		/*ivtv_vapi(itv, CX2341X_ENC_SET_DMA_BLOCK_SIZE, 2, 128, 0); */
		ivtv_vapi(itv, CX2341X_ENC_SET_DMA_BLOCK_SIZE, 2, 1, 1);

		/* Stuff from Windows, we don't know what it is */
		ivtv_vapi(itv, CX2341X_ENC_SET_VERT_CROP_LINE, 1, 0);
		/* According to the docs, this should be correct. However, this is
		   untested. I don't dare enable this without having tested it.
		   Only very few old cards actually have this hardware combination.
		ivtv_vapi(itv, CX2341X_ENC_SET_VERT_CROP_LINE, 1,
			((itv->hw_flags & IVTV_HW_SAA7114) && itv->is_60hz) ? 10001 : 0);
		*/
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 3, !itv->has_cx23415);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 8, 0);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 4, 1);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12);

		/* assign placeholder */
		ivtv_vapi(itv, CX2341X_ENC_SET_PLACEHOLDER, 12,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		if (itv->card->hw_all & (IVTV_HW_SAA7115 | IVTV_HW_SAA717X))
		    digitizer = 0xF1;
		else if (itv->card->hw_all & IVTV_HW_SAA7114)
		    digitizer = 0xEF;
		else /* cx25840 */
		    digitizer = 0x140;

		ivtv_vapi(itv, CX2341X_ENC_SET_NUM_VSYNC_LINES, 2, digitizer, digitizer);

		/* Setup VBI */
		if (itv->v4l2_cap & V4L2_CAP_VBI_CAPTURE) {
			ivtv_vbi_setup(itv);
		}

		/* assign program index info. Mask 7: select I/P/B, Num_req: 400 max */
		ivtv_vapi_result(itv, data, CX2341X_ENC_SET_PGM_INDEX_INFO, 2, 7, 400);
		itv->pgm_info_offset = data[0];
		itv->pgm_info_num = data[1];
		itv->pgm_info_write_idx = 0;
		itv->pgm_info_read_idx = 0;

		IVTV_DEBUG_INFO("PGM Index at 0x%08x with %d elements\n",
				itv->pgm_info_offset, itv->pgm_info_num);

		/* Setup API for Stream */
		cx2341x_handler_setup(&itv->cxhdl);

		/* mute if capturing radio */
		if (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags))
			ivtv_vapi(itv, CX2341X_ENC_MUTE_VIDEO, 1,
				1 | (v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute_yuv) << 8));
	}

	/* Vsync Setup */
	if (itv->has_cx23415 && !test_and_set_bit(IVTV_F_I_DIG_RST, &itv->i_flags)) {
		/* event notification (on) */
		ivtv_vapi(itv, CX2341X_ENC_SET_EVENT_NOTIFICATION, 4, 0, 1, IVTV_IRQ_ENC_VIM_RST, -1);
		ivtv_clear_irq_mask(itv, IVTV_IRQ_ENC_VIM_RST);
	}

	if (atomic_read(&itv->capturing) == 0) {
		/* Clear all Pending Interrupts */
		ivtv_set_irq_mask(itv, IVTV_IRQ_MASK_CAPTURE);

		clear_bit(IVTV_F_I_EOS, &itv->i_flags);

		cx2341x_handler_set_busy(&itv->cxhdl, 1);

		/* Initialize Digitizer for Capture */
		/* Avoid tinny audio problem - ensure audio clocks are going */
		v4l2_subdev_call(itv->sd_audio, audio, s_stream, 1);
		/* Avoid unpredictable PCI bus hang - disable video clocks */
		v4l2_subdev_call(itv->sd_video, video, s_stream, 0);
		ivtv_msleep_timeout(300, 0);
		ivtv_vapi(itv, CX2341X_ENC_INITIALIZE_INPUT, 0);
		v4l2_subdev_call(itv->sd_video, video, s_stream, 1);
	}

	/* begin_capture */
	if (ivtv_vapi(itv, CX2341X_ENC_START_CAPTURE, 2, captype, subtype))
	{
		IVTV_DEBUG_WARN( "Error starting capture!\n");
		return -EINVAL;
	}

	/* Start Passthrough */
	if (enable_passthrough) {
		ivtv_passthrough_mode(itv, 1);
	}

	if (s->type == IVTV_ENC_STREAM_TYPE_VBI)
		ivtv_clear_irq_mask(itv, IVTV_IRQ_ENC_VBI_CAP);
	else
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_CAPTURE);

	/* you're live! sit back and await interrupts :) */
	atomic_inc(&itv->capturing);
	return 0;
}