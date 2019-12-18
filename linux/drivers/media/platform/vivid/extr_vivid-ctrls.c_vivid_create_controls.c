#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_13__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_12__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_11__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_10__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_9__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_8__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct vivid_dev {int* input_brightness; TYPE_7__ sdr_cap_dev; scalar_t__ has_sdr_cap; TYPE_6__ radio_tx_dev; scalar_t__ has_radio_tx; TYPE_5__ radio_rx_dev; scalar_t__ has_radio_rx; TYPE_4__ vbi_out_dev; scalar_t__ has_vbi_out; TYPE_3__ vbi_cap_dev; scalar_t__ has_vbi_cap; TYPE_2__ vid_out_dev; scalar_t__ has_vid_out; TYPE_1__ vid_cap_dev; scalar_t__ has_vid_cap; void* autogain; void* radio_tx_rds_ms; void* radio_tx_rds_tp; void* radio_tx_rds_ta; void* radio_tx_rds_dyn_pty; void* radio_tx_rds_compressed; void* radio_tx_rds_art_head; void* radio_tx_rds_mono_stereo; void* radio_tx_rds_radiotext; void* radio_tx_rds_psname; void* radio_tx_rds_pty; void* radio_tx_rds_pi; void* radio_rx_rds_ms; void* radio_rx_rds_tp; void* radio_rx_rds_ta; void* radio_rx_rds_radiotext; void* radio_rx_rds_psname; void* radio_rx_rds_pty; scalar_t__ has_fb; void* ctrl_tx_edid_present; void* ctrl_tx_rxsense; void* ctrl_tx_hotplug; void* ctrl_display_present; void* ctrl_tx_mode; void* ctrl_tx_rgb_range; scalar_t__ num_hdmi_outputs; void* ctrl_rx_power_present; void* rgb_range_cap; void* real_rgb_range_cap; void* ctrl_dv_timings_signal_mode; void* ctrl_dv_timings; scalar_t__ query_dv_timings_qmenu; scalar_t__ query_dv_timings_size; scalar_t__ num_hdmi_inputs; scalar_t__ has_raw_vbi_cap; void* ctrl_std_signal_mode; void* ctrl_standard; void* ctrl_has_scaler_out; void* ctrl_has_compose_out; void* ctrl_has_crop_out; void* colorspace; void* ctrl_has_scaler_cap; void* ctrl_has_compose_cap; void* ctrl_has_crop_cap; void* test_pattern; void* int_menu; void* bitmask; void* string; void* menu; void* boolean; void* int64; void* int32; void* button; void* alpha; void* gain; void* hue; void* saturation; void* contrast; void* brightness; void* mute; void* volume; struct v4l2_ctrl_handler ctrl_hdl_sdr_cap; struct v4l2_ctrl_handler ctrl_hdl_radio_tx; struct v4l2_ctrl_handler ctrl_hdl_radio_rx; struct v4l2_ctrl_handler ctrl_hdl_vbi_out; struct v4l2_ctrl_handler ctrl_hdl_vbi_cap; struct v4l2_ctrl_handler ctrl_hdl_vid_out; struct v4l2_ctrl_handler ctrl_hdl_vid_cap; struct v4l2_ctrl_handler ctrl_hdl_fb; struct v4l2_ctrl_handler ctrl_hdl_loop_cap; struct v4l2_ctrl_handler ctrl_hdl_sdtv_cap; struct v4l2_ctrl_handler ctrl_hdl_streaming; struct v4l2_ctrl_handler ctrl_hdl_user_aud; struct v4l2_ctrl_handler ctrl_hdl_user_vid; struct v4l2_ctrl_handler ctrl_hdl_user_gen; } ;
struct v4l2_ctrl_config {char* name; char const* const* qmenu; scalar_t__ max; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/ * ops; } ;
typedef  int s64 ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int MAX_INPUTS ; 
 scalar_t__ TPG_PAT_NOISE ; 
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_DV_RX_POWER_PRESENT ; 
 int /*<<< orphan*/  V4L2_CID_DV_RX_RGB_RANGE ; 
 int /*<<< orphan*/  V4L2_CID_DV_TX_EDID_PRESENT ; 
 int /*<<< orphan*/  V4L2_CID_DV_TX_HOTPLUG ; 
 int /*<<< orphan*/  V4L2_CID_DV_TX_MODE ; 
 int /*<<< orphan*/  V4L2_CID_DV_TX_RGB_RANGE ; 
 int /*<<< orphan*/  V4L2_CID_DV_TX_RXSENSE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RECEPTION ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_MUSIC_SPEECH ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_PS_NAME ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_PTY ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_RADIO_TEXT ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT ; 
 int /*<<< orphan*/  V4L2_CID_RDS_RX_TRAFFIC_PROGRAM ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_ARTIFICIAL_HEAD ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_DYNAMIC_PTY ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_MONO_STEREO ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_MUSIC_SPEECH ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PI ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PS_NAME ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PTY ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_RADIO_TEXT ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_TRAFFIC_PROGRAM ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_CTRL_TYPE_MENU ; 
 int /*<<< orphan*/  V4L2_DV_RGB_RANGE_AUTO ; 
 int /*<<< orphan*/  V4L2_DV_RGB_RANGE_FULL ; 
 int /*<<< orphan*/  V4L2_DV_TX_MODE_HDMI ; 
 int /*<<< orphan*/  VIVID_CID_DV_TIMINGS ; 
 int /*<<< orphan*/  VIVID_CID_TEST_PATTERN ; 
 char const* const* tpg_pattern_strings ; 
 int /*<<< orphan*/  v4l2_ctrl_add_handler (struct v4l2_ctrl_handler*,struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,struct v4l2_ctrl_config*,int /*<<< orphan*/ *) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl_string (void*,char*) ; 
 struct v4l2_ctrl_config vivid_ctrl_alpha_mode ; 
 struct v4l2_ctrl_config vivid_ctrl_bitmask ; 
 struct v4l2_ctrl_config vivid_ctrl_boolean ; 
 struct v4l2_ctrl_config vivid_ctrl_buf_prepare_error ; 
 struct v4l2_ctrl_config vivid_ctrl_button ; 
 struct v4l2_ctrl_config vivid_ctrl_class ; 
 struct v4l2_ctrl_config vivid_ctrl_clear_fb ; 
 struct v4l2_ctrl_config vivid_ctrl_colorspace ; 
 struct v4l2_ctrl_config vivid_ctrl_disconnect ; 
 struct v4l2_ctrl_config vivid_ctrl_display_present ; 
 struct v4l2_ctrl_config vivid_ctrl_dqbuf_error ; 
 struct v4l2_ctrl_config vivid_ctrl_dv_timings_aspect_ratio ; 
 struct v4l2_ctrl_config vivid_ctrl_dv_timings_signal_mode ; 
 struct v4l2_ctrl_config vivid_ctrl_has_compose_cap ; 
 struct v4l2_ctrl_config vivid_ctrl_has_compose_out ; 
 struct v4l2_ctrl_config vivid_ctrl_has_crop_cap ; 
 struct v4l2_ctrl_config vivid_ctrl_has_crop_out ; 
 struct v4l2_ctrl_config vivid_ctrl_has_scaler_cap ; 
 struct v4l2_ctrl_config vivid_ctrl_has_scaler_out ; 
 struct v4l2_ctrl_config vivid_ctrl_hflip ; 
 struct v4l2_ctrl_config vivid_ctrl_hor_movement ; 
 struct v4l2_ctrl_config vivid_ctrl_hsv_enc ; 
 struct v4l2_ctrl_config vivid_ctrl_insert_eav ; 
 struct v4l2_ctrl_config vivid_ctrl_insert_sav ; 
 struct v4l2_ctrl_config vivid_ctrl_int32 ; 
 struct v4l2_ctrl_config vivid_ctrl_int64 ; 
 struct v4l2_ctrl_config vivid_ctrl_int_menu ; 
 struct v4l2_ctrl_config vivid_ctrl_limited_rgb_range ; 
 struct v4l2_ctrl_config vivid_ctrl_loop_video ; 
 struct v4l2_ctrl_config vivid_ctrl_max_edid_blocks ; 
 struct v4l2_ctrl_config vivid_ctrl_menu ; 
 struct v4l2_ctrl_config vivid_ctrl_osd_mode ; 
 struct v4l2_ctrl_config vivid_ctrl_perc_dropped ; 
 struct v4l2_ctrl_config vivid_ctrl_perc_fill ; 
 struct v4l2_ctrl_config vivid_ctrl_quantization ; 
 struct v4l2_ctrl_config vivid_ctrl_queue_error ; 
 struct v4l2_ctrl_config vivid_ctrl_queue_setup_error ; 
 struct v4l2_ctrl_config vivid_ctrl_radio_hw_seek_mode ; 
 struct v4l2_ctrl_config vivid_ctrl_radio_hw_seek_prog_lim ; 
 struct v4l2_ctrl_config vivid_ctrl_radio_rx_rds_blockio ; 
 struct v4l2_ctrl_config vivid_ctrl_radio_rx_rds_rbds ; 
 struct v4l2_ctrl_config vivid_ctrl_radio_tx_rds_blockio ; 
 struct v4l2_ctrl_config vivid_ctrl_reduced_fps ; 
 struct v4l2_ctrl_config vivid_ctrl_req_validate_error ; 
 struct v4l2_ctrl_config vivid_ctrl_sdr_cap_fm_deviation ; 
 struct v4l2_ctrl_config vivid_ctrl_seq_wrap ; 
 struct v4l2_ctrl_config vivid_ctrl_show_border ; 
 struct v4l2_ctrl_config vivid_ctrl_show_square ; 
 struct v4l2_ctrl_config vivid_ctrl_standard ; 
 struct v4l2_ctrl_config vivid_ctrl_start_streaming_error ; 
 struct v4l2_ctrl_config vivid_ctrl_std_aspect_ratio ; 
 struct v4l2_ctrl_config vivid_ctrl_std_signal_mode ; 
 struct v4l2_ctrl_config vivid_ctrl_string ; 
 struct v4l2_ctrl_config vivid_ctrl_time_wrap ; 
 struct v4l2_ctrl_config vivid_ctrl_tstamp_src ; 
 struct v4l2_ctrl_config vivid_ctrl_u16_matrix ; 
 struct v4l2_ctrl_config vivid_ctrl_u32_array ; 
 struct v4l2_ctrl_config vivid_ctrl_u8_4d_array ; 
 struct v4l2_ctrl_config vivid_ctrl_vbi_cap_interlaced ; 
 struct v4l2_ctrl_config vivid_ctrl_vert_movement ; 
 struct v4l2_ctrl_config vivid_ctrl_vflip ; 
 struct v4l2_ctrl_config vivid_ctrl_xfer_func ; 
 struct v4l2_ctrl_config vivid_ctrl_ycbcr_enc ; 
 int /*<<< orphan*/  vivid_radio_rx_ctrl_ops ; 
 int /*<<< orphan*/  vivid_radio_tx_ctrl_ops ; 
 int /*<<< orphan*/  vivid_user_vid_ctrl_ops ; 
 int /*<<< orphan*/  vivid_vid_cap_ctrl_ops ; 

int vivid_create_controls(struct vivid_dev *dev, bool show_ccs_cap,
		bool show_ccs_out, bool no_error_inj,
		bool has_sdtv, bool has_hdmi)
{
	struct v4l2_ctrl_handler *hdl_user_gen = &dev->ctrl_hdl_user_gen;
	struct v4l2_ctrl_handler *hdl_user_vid = &dev->ctrl_hdl_user_vid;
	struct v4l2_ctrl_handler *hdl_user_aud = &dev->ctrl_hdl_user_aud;
	struct v4l2_ctrl_handler *hdl_streaming = &dev->ctrl_hdl_streaming;
	struct v4l2_ctrl_handler *hdl_sdtv_cap = &dev->ctrl_hdl_sdtv_cap;
	struct v4l2_ctrl_handler *hdl_loop_cap = &dev->ctrl_hdl_loop_cap;
	struct v4l2_ctrl_handler *hdl_fb = &dev->ctrl_hdl_fb;
	struct v4l2_ctrl_handler *hdl_vid_cap = &dev->ctrl_hdl_vid_cap;
	struct v4l2_ctrl_handler *hdl_vid_out = &dev->ctrl_hdl_vid_out;
	struct v4l2_ctrl_handler *hdl_vbi_cap = &dev->ctrl_hdl_vbi_cap;
	struct v4l2_ctrl_handler *hdl_vbi_out = &dev->ctrl_hdl_vbi_out;
	struct v4l2_ctrl_handler *hdl_radio_rx = &dev->ctrl_hdl_radio_rx;
	struct v4l2_ctrl_handler *hdl_radio_tx = &dev->ctrl_hdl_radio_tx;
	struct v4l2_ctrl_handler *hdl_sdr_cap = &dev->ctrl_hdl_sdr_cap;
	struct v4l2_ctrl_config vivid_ctrl_dv_timings = {
		.ops = &vivid_vid_cap_ctrl_ops,
		.id = VIVID_CID_DV_TIMINGS,
		.name = "DV Timings",
		.type = V4L2_CTRL_TYPE_MENU,
	};
	int i;

	v4l2_ctrl_handler_init(hdl_user_gen, 10);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_user_vid, 9);
	v4l2_ctrl_new_custom(hdl_user_vid, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_user_aud, 2);
	v4l2_ctrl_new_custom(hdl_user_aud, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_streaming, 8);
	v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_sdtv_cap, 2);
	v4l2_ctrl_new_custom(hdl_sdtv_cap, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_loop_cap, 1);
	v4l2_ctrl_new_custom(hdl_loop_cap, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_fb, 1);
	v4l2_ctrl_new_custom(hdl_fb, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_vid_cap, 55);
	v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_vid_out, 26);
	if (!no_error_inj || dev->has_fb || dev->num_hdmi_outputs)
		v4l2_ctrl_new_custom(hdl_vid_out, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_vbi_cap, 21);
	v4l2_ctrl_new_custom(hdl_vbi_cap, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_vbi_out, 19);
	if (!no_error_inj)
		v4l2_ctrl_new_custom(hdl_vbi_out, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_radio_rx, 17);
	v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_radio_tx, 17);
	v4l2_ctrl_new_custom(hdl_radio_tx, &vivid_ctrl_class, NULL);
	v4l2_ctrl_handler_init(hdl_sdr_cap, 19);
	v4l2_ctrl_new_custom(hdl_sdr_cap, &vivid_ctrl_class, NULL);

	/* User Controls */
	dev->volume = v4l2_ctrl_new_std(hdl_user_aud, NULL,
		V4L2_CID_AUDIO_VOLUME, 0, 255, 1, 200);
	dev->mute = v4l2_ctrl_new_std(hdl_user_aud, NULL,
		V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	if (dev->has_vid_cap) {
		dev->brightness = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
		for (i = 0; i < MAX_INPUTS; i++)
			dev->input_brightness[i] = 128;
		dev->contrast = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
		dev->saturation = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
		dev->hue = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_HUE, -128, 128, 1, 0);
		v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
		v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
		dev->autogain = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		dev->gain = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 100);
		dev->alpha = v4l2_ctrl_new_std(hdl_user_vid, &vivid_user_vid_ctrl_ops,
			V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 0);
	}
	dev->button = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_button, NULL);
	dev->int32 = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_int32, NULL);
	dev->int64 = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_int64, NULL);
	dev->boolean = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_boolean, NULL);
	dev->menu = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_menu, NULL);
	dev->string = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_string, NULL);
	dev->bitmask = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_bitmask, NULL);
	dev->int_menu = v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_int_menu, NULL);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u32_array, NULL);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u16_matrix, NULL);
	v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_u8_4d_array, NULL);

	if (dev->has_vid_cap) {
		/* Image Processing Controls */
		struct v4l2_ctrl_config vivid_ctrl_test_pattern = {
			.ops = &vivid_vid_cap_ctrl_ops,
			.id = VIVID_CID_TEST_PATTERN,
			.name = "Test Pattern",
			.type = V4L2_CTRL_TYPE_MENU,
			.max = TPG_PAT_NOISE,
			.qmenu = tpg_pattern_strings,
		};

		dev->test_pattern = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_test_pattern, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_perc_fill, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hor_movement, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_vert_movement, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_osd_mode, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_show_border, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_show_square, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hflip, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_vflip, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_insert_sav, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_insert_eav, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_reduced_fps, NULL);
		if (show_ccs_cap) {
			dev->ctrl_has_crop_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_crop_cap, NULL);
			dev->ctrl_has_compose_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_compose_cap, NULL);
			dev->ctrl_has_scaler_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
				&vivid_ctrl_has_scaler_cap, NULL);
		}

		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_tstamp_src, NULL);
		dev->colorspace = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_colorspace, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_xfer_func, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_ycbcr_enc, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_hsv_enc, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_quantization, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_alpha_mode, NULL);
	}

	if (dev->has_vid_out && show_ccs_out) {
		dev->ctrl_has_crop_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_crop_out, NULL);
		dev->ctrl_has_compose_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_compose_out, NULL);
		dev->ctrl_has_scaler_out = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_has_scaler_out, NULL);
	}

	/*
	 * Testing this driver with v4l2-compliance will trigger the error
	 * injection controls, and after that nothing will work as expected.
	 * So we have a module option to drop these error injecting controls
	 * allowing us to run v4l2_compliance again.
	 */
	if (!no_error_inj) {
		v4l2_ctrl_new_custom(hdl_user_gen, &vivid_ctrl_disconnect, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_dqbuf_error, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_perc_dropped, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_queue_setup_error, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_buf_prepare_error, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_start_streaming_error, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_queue_error, NULL);
#ifdef CONFIG_MEDIA_CONTROLLER
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_req_validate_error, NULL);
#endif
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_seq_wrap, NULL);
		v4l2_ctrl_new_custom(hdl_streaming, &vivid_ctrl_time_wrap, NULL);
	}

	if (has_sdtv && (dev->has_vid_cap || dev->has_vbi_cap)) {
		if (dev->has_vid_cap)
			v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_std_aspect_ratio, NULL);
		dev->ctrl_std_signal_mode = v4l2_ctrl_new_custom(hdl_sdtv_cap,
			&vivid_ctrl_std_signal_mode, NULL);
		dev->ctrl_standard = v4l2_ctrl_new_custom(hdl_sdtv_cap,
			&vivid_ctrl_standard, NULL);
		if (dev->ctrl_std_signal_mode)
			v4l2_ctrl_cluster(2, &dev->ctrl_std_signal_mode);
		if (dev->has_raw_vbi_cap)
			v4l2_ctrl_new_custom(hdl_vbi_cap, &vivid_ctrl_vbi_cap_interlaced, NULL);
	}

	if (dev->num_hdmi_inputs) {
		s64 hdmi_input_mask = GENMASK(dev->num_hdmi_inputs - 1, 0);

		dev->ctrl_dv_timings_signal_mode = v4l2_ctrl_new_custom(hdl_vid_cap,
					&vivid_ctrl_dv_timings_signal_mode, NULL);

		vivid_ctrl_dv_timings.max = dev->query_dv_timings_size - 1;
		vivid_ctrl_dv_timings.qmenu =
			(const char * const *)dev->query_dv_timings_qmenu;
		dev->ctrl_dv_timings = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_dv_timings, NULL);
		if (dev->ctrl_dv_timings_signal_mode)
			v4l2_ctrl_cluster(2, &dev->ctrl_dv_timings_signal_mode);

		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_dv_timings_aspect_ratio, NULL);
		v4l2_ctrl_new_custom(hdl_vid_cap, &vivid_ctrl_max_edid_blocks, NULL);
		dev->real_rgb_range_cap = v4l2_ctrl_new_custom(hdl_vid_cap,
			&vivid_ctrl_limited_rgb_range, NULL);
		dev->rgb_range_cap = v4l2_ctrl_new_std_menu(hdl_vid_cap,
			&vivid_vid_cap_ctrl_ops,
			V4L2_CID_DV_RX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
		dev->ctrl_rx_power_present = v4l2_ctrl_new_std(hdl_vid_cap,
			NULL, V4L2_CID_DV_RX_POWER_PRESENT, 0, hdmi_input_mask,
			0, hdmi_input_mask);

	}
	if (dev->num_hdmi_outputs) {
		s64 hdmi_output_mask = GENMASK(dev->num_hdmi_outputs - 1, 0);

		/*
		 * We aren't doing anything with this at the moment, but
		 * HDMI outputs typically have this controls.
		 */
		dev->ctrl_tx_rgb_range = v4l2_ctrl_new_std_menu(hdl_vid_out, NULL,
			V4L2_CID_DV_TX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL,
			0, V4L2_DV_RGB_RANGE_AUTO);
		dev->ctrl_tx_mode = v4l2_ctrl_new_std_menu(hdl_vid_out, NULL,
			V4L2_CID_DV_TX_MODE, V4L2_DV_TX_MODE_HDMI,
			0, V4L2_DV_TX_MODE_HDMI);
		dev->ctrl_display_present = v4l2_ctrl_new_custom(hdl_vid_out,
			&vivid_ctrl_display_present, NULL);
		dev->ctrl_tx_hotplug = v4l2_ctrl_new_std(hdl_vid_out,
			NULL, V4L2_CID_DV_TX_HOTPLUG, 0, hdmi_output_mask,
			0, hdmi_output_mask);
		dev->ctrl_tx_rxsense = v4l2_ctrl_new_std(hdl_vid_out,
			NULL, V4L2_CID_DV_TX_RXSENSE, 0, hdmi_output_mask,
			0, hdmi_output_mask);
		dev->ctrl_tx_edid_present = v4l2_ctrl_new_std(hdl_vid_out,
			NULL, V4L2_CID_DV_TX_EDID_PRESENT, 0, hdmi_output_mask,
			0, hdmi_output_mask);
	}
	if ((dev->has_vid_cap && dev->has_vid_out) ||
	    (dev->has_vbi_cap && dev->has_vbi_out))
		v4l2_ctrl_new_custom(hdl_loop_cap, &vivid_ctrl_loop_video, NULL);

	if (dev->has_fb)
		v4l2_ctrl_new_custom(hdl_fb, &vivid_ctrl_clear_fb, NULL);

	if (dev->has_radio_rx) {
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_hw_seek_mode, NULL);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_hw_seek_prog_lim, NULL);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_rx_rds_blockio, NULL);
		v4l2_ctrl_new_custom(hdl_radio_rx, &vivid_ctrl_radio_rx_rds_rbds, NULL);
		v4l2_ctrl_new_std(hdl_radio_rx, &vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RECEPTION, 0, 1, 1, 1);
		dev->radio_rx_rds_pty = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_PTY, 0, 31, 1, 0);
		dev->radio_rx_rds_psname = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_PS_NAME, 0, 8, 8, 0);
		dev->radio_rx_rds_radiotext = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_RADIO_TEXT, 0, 64, 64, 0);
		dev->radio_rx_rds_ta = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
		dev->radio_rx_rds_tp = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_TRAFFIC_PROGRAM, 0, 1, 1, 0);
		dev->radio_rx_rds_ms = v4l2_ctrl_new_std(hdl_radio_rx,
			&vivid_radio_rx_ctrl_ops,
			V4L2_CID_RDS_RX_MUSIC_SPEECH, 0, 1, 1, 1);
	}
	if (dev->has_radio_tx) {
		v4l2_ctrl_new_custom(hdl_radio_tx,
			&vivid_ctrl_radio_tx_rds_blockio, NULL);
		dev->radio_tx_rds_pi = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PI, 0, 0xffff, 1, 0x8088);
		dev->radio_tx_rds_pty = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PTY, 0, 31, 1, 3);
		dev->radio_tx_rds_psname = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_PS_NAME, 0, 8, 8, 0);
		if (dev->radio_tx_rds_psname)
			v4l2_ctrl_s_ctrl_string(dev->radio_tx_rds_psname, "VIVID-TX");
		dev->radio_tx_rds_radiotext = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_RADIO_TEXT, 0, 64 * 2, 64, 0);
		if (dev->radio_tx_rds_radiotext)
			v4l2_ctrl_s_ctrl_string(dev->radio_tx_rds_radiotext,
			       "This is a VIVID default Radio Text template text, change at will");
		dev->radio_tx_rds_mono_stereo = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_MONO_STEREO, 0, 1, 1, 1);
		dev->radio_tx_rds_art_head = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_ARTIFICIAL_HEAD, 0, 1, 1, 0);
		dev->radio_tx_rds_compressed = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_COMPRESSED, 0, 1, 1, 0);
		dev->radio_tx_rds_dyn_pty = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_DYNAMIC_PTY, 0, 1, 1, 0);
		dev->radio_tx_rds_ta = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
		dev->radio_tx_rds_tp = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_PROGRAM, 0, 1, 1, 1);
		dev->radio_tx_rds_ms = v4l2_ctrl_new_std(hdl_radio_tx,
			&vivid_radio_tx_ctrl_ops,
			V4L2_CID_RDS_TX_MUSIC_SPEECH, 0, 1, 1, 1);
	}
	if (dev->has_sdr_cap) {
		v4l2_ctrl_new_custom(hdl_sdr_cap,
			&vivid_ctrl_sdr_cap_fm_deviation, NULL);
	}
	if (hdl_user_gen->error)
		return hdl_user_gen->error;
	if (hdl_user_vid->error)
		return hdl_user_vid->error;
	if (hdl_user_aud->error)
		return hdl_user_aud->error;
	if (hdl_streaming->error)
		return hdl_streaming->error;
	if (hdl_sdr_cap->error)
		return hdl_sdr_cap->error;
	if (hdl_loop_cap->error)
		return hdl_loop_cap->error;

	if (dev->autogain)
		v4l2_ctrl_auto_cluster(2, &dev->autogain, 0, true);

	if (dev->has_vid_cap) {
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_vid, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_user_aud, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_streaming, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_sdtv_cap, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_loop_cap, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_cap, hdl_fb, NULL, false);
		if (hdl_vid_cap->error)
			return hdl_vid_cap->error;
		dev->vid_cap_dev.ctrl_handler = hdl_vid_cap;
	}
	if (dev->has_vid_out) {
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_user_aud, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_streaming, NULL, false);
		v4l2_ctrl_add_handler(hdl_vid_out, hdl_fb, NULL, false);
		if (hdl_vid_out->error)
			return hdl_vid_out->error;
		dev->vid_out_dev.ctrl_handler = hdl_vid_out;
	}
	if (dev->has_vbi_cap) {
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_streaming, NULL, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_sdtv_cap, NULL, false);
		v4l2_ctrl_add_handler(hdl_vbi_cap, hdl_loop_cap, NULL, false);
		if (hdl_vbi_cap->error)
			return hdl_vbi_cap->error;
		dev->vbi_cap_dev.ctrl_handler = hdl_vbi_cap;
	}
	if (dev->has_vbi_out) {
		v4l2_ctrl_add_handler(hdl_vbi_out, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_vbi_out, hdl_streaming, NULL, false);
		if (hdl_vbi_out->error)
			return hdl_vbi_out->error;
		dev->vbi_out_dev.ctrl_handler = hdl_vbi_out;
	}
	if (dev->has_radio_rx) {
		v4l2_ctrl_add_handler(hdl_radio_rx, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_radio_rx, hdl_user_aud, NULL, false);
		if (hdl_radio_rx->error)
			return hdl_radio_rx->error;
		dev->radio_rx_dev.ctrl_handler = hdl_radio_rx;
	}
	if (dev->has_radio_tx) {
		v4l2_ctrl_add_handler(hdl_radio_tx, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_radio_tx, hdl_user_aud, NULL, false);
		if (hdl_radio_tx->error)
			return hdl_radio_tx->error;
		dev->radio_tx_dev.ctrl_handler = hdl_radio_tx;
	}
	if (dev->has_sdr_cap) {
		v4l2_ctrl_add_handler(hdl_sdr_cap, hdl_user_gen, NULL, false);
		v4l2_ctrl_add_handler(hdl_sdr_cap, hdl_streaming, NULL, false);
		if (hdl_sdr_cap->error)
			return hdl_sdr_cap->error;
		dev->sdr_cap_dev.ctrl_handler = hdl_sdr_cap;
	}
	return 0;
}