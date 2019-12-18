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
struct omap_video_timings {int dummy; } ;
struct hdmi_wp_data {int dummy; } ;
struct hdmi_video_format {int /*<<< orphan*/  packing_mode; } ;
struct hdmi_core_vid_config {int /*<<< orphan*/  packet_mode; } ;
struct hdmi_core_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  quantization_range; } ;
struct hdmi_config {scalar_t__ hdmi_dvi_mode; TYPE_1__ infoframe; } ;

/* Variables and functions */
 scalar_t__ HDMI_HDMI ; 
 int /*<<< orphan*/  HDMI_PACKETMODE24BITPERPIXEL ; 
 int /*<<< orphan*/  HDMI_PACK_24b_RGB_YUV444_YUV422 ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int /*<<< orphan*/  hdmi_core_config_csc (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_config_video_packetizer (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_config_video_sampler (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_configure_range (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_enable_interrupts (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_enable_video_path (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_init (struct hdmi_core_vid_config*,struct hdmi_config*) ; 
 int /*<<< orphan*/  hdmi_core_mask_interrupts (struct hdmi_core_data*) ; 
 int /*<<< orphan*/  hdmi_core_video_config (struct hdmi_core_data*,struct hdmi_core_vid_config*) ; 
 int /*<<< orphan*/  hdmi_core_write_avi_infoframe (struct hdmi_core_data*,TYPE_1__*) ; 
 int /*<<< orphan*/  hdmi_wp_init_vid_fmt_timings (struct hdmi_video_format*,struct omap_video_timings*,struct hdmi_config*) ; 
 int /*<<< orphan*/  hdmi_wp_video_config_format (struct hdmi_wp_data*,struct hdmi_video_format*) ; 
 int /*<<< orphan*/  hdmi_wp_video_config_interface (struct hdmi_wp_data*,struct omap_video_timings*) ; 
 int /*<<< orphan*/  hdmi_wp_video_config_timing (struct hdmi_wp_data*,struct omap_video_timings*) ; 

void hdmi5_configure(struct hdmi_core_data *core, struct hdmi_wp_data *wp,
		struct hdmi_config *cfg)
{
	struct omap_video_timings video_timing;
	struct hdmi_video_format video_format;
	struct hdmi_core_vid_config v_core_cfg;

	hdmi_core_mask_interrupts(core);

	hdmi_core_init(&v_core_cfg, cfg);

	hdmi_wp_init_vid_fmt_timings(&video_format, &video_timing, cfg);

	hdmi_wp_video_config_timing(wp, &video_timing);

	/* video config */
	video_format.packing_mode = HDMI_PACK_24b_RGB_YUV444_YUV422;

	hdmi_wp_video_config_format(wp, &video_format);

	hdmi_wp_video_config_interface(wp, &video_timing);

	/* support limited range with 24 bit color depth for now */
	hdmi_core_configure_range(core);
	cfg->infoframe.quantization_range = HDMI_QUANTIZATION_RANGE_LIMITED;

	/*
	 * configure core video part, set software reset in the core
	 */
	v_core_cfg.packet_mode = HDMI_PACKETMODE24BITPERPIXEL;

	hdmi_core_video_config(core, &v_core_cfg);

	hdmi_core_config_video_packetizer(core);
	hdmi_core_config_csc(core);
	hdmi_core_config_video_sampler(core);

	if (cfg->hdmi_dvi_mode == HDMI_HDMI)
		hdmi_core_write_avi_infoframe(core, &cfg->infoframe);

	hdmi_core_enable_video_path(core);

	hdmi_core_enable_interrupts(core);
}