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
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; scalar_t__ tuner; } ;
struct ivtv_open_id {int /*<<< orphan*/  type; struct ivtv* itv; } ;
struct ivtv {int std; int active_input; int std_out; int v4l2_cap; int /*<<< orphan*/  cxhdl; int /*<<< orphan*/  tuner_std; int /*<<< orphan*/  has_cx23415; TYPE_1__* card; int /*<<< orphan*/  sd_video; int /*<<< orphan*/  i_flags; } ;
struct TYPE_2__ {int hw_all; int v4l2_capabilities; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_ENC_STREAM_TYPE_MPG ; 
 int /*<<< orphan*/  IVTV_F_I_FAILED ; 
 int /*<<< orphan*/  IVTV_F_I_INITED ; 
 int IVTV_HW_CX25840 ; 
 int /*<<< orphan*/  IVTV_HW_SAA7127 ; 
 int IVTV_IRQ_DEC_VSYNC ; 
 int IVTV_IRQ_MASK_INIT ; 
 int /*<<< orphan*/  IVTV_REG_DMACONTROL ; 
 int /*<<< orphan*/  IVTV_WARN (char*) ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int V4L2_STD_NTSC_M ; 
 int V4L2_STD_NTSC_M_JP ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx2341x_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ivtv_clear_irq_mask (struct ivtv*,int) ; 
 scalar_t__ ivtv_firmware_init (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_firmware_versions (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_init_mpeg_decoder (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_s_frequency (int /*<<< orphan*/ *,struct ivtv_open_id*,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  ivtv_s_input (int /*<<< orphan*/ *,struct ivtv_open_id*,int) ; 
 int /*<<< orphan*/  ivtv_s_std_dec (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_s_std_enc (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_set_osd_alpha (struct ivtv*) ; 
 int /*<<< orphan*/  load_fw ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  write_reg_sync (int,int /*<<< orphan*/ ) ; 

int ivtv_init_on_first_open(struct ivtv *itv)
{
	struct v4l2_frequency vf;
	/* Needed to call ioctls later */
	struct ivtv_open_id fh;
	int fw_retry_count = 3;
	int video_input;

	fh.itv = itv;
	fh.type = IVTV_ENC_STREAM_TYPE_MPG;

	if (test_bit(IVTV_F_I_FAILED, &itv->i_flags))
		return -ENXIO;

	if (test_and_set_bit(IVTV_F_I_INITED, &itv->i_flags))
		return 0;

	while (--fw_retry_count > 0) {
		/* load firmware */
		if (ivtv_firmware_init(itv) == 0)
			break;
		if (fw_retry_count > 1)
			IVTV_WARN("Retry loading firmware\n");
	}

	if (fw_retry_count == 0) {
		set_bit(IVTV_F_I_FAILED, &itv->i_flags);
		return -ENXIO;
	}

	/* Try and get firmware versions */
	IVTV_DEBUG_INFO("Getting firmware version..\n");
	ivtv_firmware_versions(itv);

	if (itv->card->hw_all & IVTV_HW_CX25840)
		v4l2_subdev_call(itv->sd_video, core, load_fw);

	vf.tuner = 0;
	vf.type = V4L2_TUNER_ANALOG_TV;
	vf.frequency = 6400; /* the tuner 'baseline' frequency */

	/* Set initial frequency. For PAL/SECAM broadcasts no
	   'default' channel exists AFAIK. */
	if (itv->std == V4L2_STD_NTSC_M_JP) {
		vf.frequency = 1460;	/* ch. 1 91250*16/1000 */
	}
	else if (itv->std & V4L2_STD_NTSC_M) {
		vf.frequency = 1076;	/* ch. 4 67250*16/1000 */
	}

	video_input = itv->active_input;
	itv->active_input++;	/* Force update of input */
	ivtv_s_input(NULL, &fh, video_input);

	/* Let the VIDIOC_S_STD ioctl do all the work, keeps the code
	   in one place. */
	itv->std++;		/* Force full standard initialization */
	itv->std_out = itv->std;
	ivtv_s_frequency(NULL, &fh, &vf);

	if (itv->card->v4l2_capabilities & V4L2_CAP_VIDEO_OUTPUT) {
		/* Turn on the TV-out: ivtv_init_mpeg_decoder() initializes
		   the mpeg decoder so now the saa7127 receives a proper
		   signal. */
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		ivtv_init_mpeg_decoder(itv);
	}

	/* On a cx23416 this seems to be able to enable DMA to the chip? */
	if (!itv->has_cx23415)
		write_reg_sync(0x03, IVTV_REG_DMACONTROL);

	ivtv_s_std_enc(itv, itv->tuner_std);

	/* Default interrupts enabled. For the PVR350 this includes the
	   decoder VSYNC interrupt, which is always on. It is not only used
	   during decoding but also by the OSD.
	   Some old PVR250 cards had a cx23415, so testing for that is too
	   general. Instead test if the card has video output capability. */
	if (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) {
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_INIT | IVTV_IRQ_DEC_VSYNC);
		ivtv_set_osd_alpha(itv);
		ivtv_s_std_dec(itv, itv->tuner_std);
	} else {
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_INIT);
	}

	/* Setup initial controls */
	cx2341x_handler_setup(&itv->cxhdl);
	return 0;
}