#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_12__ {int bits_per_pixel; int block_pred_enable; int linebuf_depth; int version_minor; scalar_t__ ycbcr422_simple; scalar_t__ num_slices_v; scalar_t__ num_slices_h; } ;
struct TYPE_19__ {int /*<<< orphan*/  LTE_340MCSC_SCRAMBLE; } ;
struct TYPE_21__ {TYPE_10__ dsc_cfg; TYPE_6__ flags; } ;
struct TYPE_17__ {int /*<<< orphan*/  all; } ;
struct TYPE_18__ {size_t mode_count; int* port_id; TYPE_4__ flags; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacture_id; int /*<<< orphan*/  display_name; int /*<<< orphan*/  video_latency; int /*<<< orphan*/  audio_latency; TYPE_2__* modes; } ;
struct dc_stream_state {TYPE_9__* ctx; int /*<<< orphan*/  stream_id; TYPE_11__* out_transfer_func; TYPE_8__ timing; TYPE_5__ audio_info; int /*<<< orphan*/  qy_bit; int /*<<< orphan*/  qs_bit; int /*<<< orphan*/  converter_disable_audio; int /*<<< orphan*/  sink_patches; int /*<<< orphan*/  link; struct dc_sink* sink; } ;
struct TYPE_20__ {size_t audio_mode_count; int /*<<< orphan*/  lte_340mcsc_scramble; int /*<<< orphan*/  speaker_flags; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacturer_id; int /*<<< orphan*/  display_name; int /*<<< orphan*/  video_latency; int /*<<< orphan*/  audio_latency; TYPE_3__* audio_modes; int /*<<< orphan*/  qy_bit; int /*<<< orphan*/  qs_bit; int /*<<< orphan*/  panel_patch; } ;
struct dc_sink {TYPE_7__ edid_caps; struct dc_container_id* dc_container_id; int /*<<< orphan*/  converter_disable_audio; int /*<<< orphan*/  link; TYPE_9__* ctx; } ;
struct dc_container_id {int* portId; } ;
struct TYPE_22__ {int /*<<< orphan*/  dc_stream_id_count; } ;
struct TYPE_16__ {int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format_code; int /*<<< orphan*/  channel_count; } ;
struct TYPE_14__ {int /*<<< orphan*/  all; } ;
struct TYPE_15__ {int /*<<< orphan*/  sample_size; TYPE_1__ sample_rates; int /*<<< orphan*/  format_code; int /*<<< orphan*/  channel_count; } ;
struct TYPE_13__ {TYPE_9__* ctx; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS ; 
 int /*<<< orphan*/  TF_TYPE_BYPASS ; 
 TYPE_11__* dc_create_transfer_func () ; 
 int /*<<< orphan*/  dc_sink_retain (struct dc_sink*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_stream_signal (struct dc_stream_state*,struct dc_sink*) ; 

__attribute__((used)) static void construct(struct dc_stream_state *stream,
	struct dc_sink *dc_sink_data)
{
	uint32_t i = 0;

	stream->sink = dc_sink_data;
	dc_sink_retain(dc_sink_data);

	stream->ctx = dc_sink_data->ctx;
	stream->link = dc_sink_data->link;
	stream->sink_patches = dc_sink_data->edid_caps.panel_patch;
	stream->converter_disable_audio = dc_sink_data->converter_disable_audio;
	stream->qs_bit = dc_sink_data->edid_caps.qs_bit;
	stream->qy_bit = dc_sink_data->edid_caps.qy_bit;

	/* Copy audio modes */
	/* TODO - Remove this translation */
	for (i = 0; i < (dc_sink_data->edid_caps.audio_mode_count); i++)
	{
		stream->audio_info.modes[i].channel_count = dc_sink_data->edid_caps.audio_modes[i].channel_count;
		stream->audio_info.modes[i].format_code = dc_sink_data->edid_caps.audio_modes[i].format_code;
		stream->audio_info.modes[i].sample_rates.all = dc_sink_data->edid_caps.audio_modes[i].sample_rate;
		stream->audio_info.modes[i].sample_size = dc_sink_data->edid_caps.audio_modes[i].sample_size;
	}
	stream->audio_info.mode_count = dc_sink_data->edid_caps.audio_mode_count;
	stream->audio_info.audio_latency = dc_sink_data->edid_caps.audio_latency;
	stream->audio_info.video_latency = dc_sink_data->edid_caps.video_latency;
	memmove(
		stream->audio_info.display_name,
		dc_sink_data->edid_caps.display_name,
		AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS);
	stream->audio_info.manufacture_id = dc_sink_data->edid_caps.manufacturer_id;
	stream->audio_info.product_id = dc_sink_data->edid_caps.product_id;
	stream->audio_info.flags.all = dc_sink_data->edid_caps.speaker_flags;

	if (dc_sink_data->dc_container_id != NULL) {
		struct dc_container_id *dc_container_id = dc_sink_data->dc_container_id;

		stream->audio_info.port_id[0] = dc_container_id->portId[0];
		stream->audio_info.port_id[1] = dc_container_id->portId[1];
	} else {
		/* TODO - WindowDM has implemented,
		other DMs need Unhardcode port_id */
		stream->audio_info.port_id[0] = 0x5558859e;
		stream->audio_info.port_id[1] = 0xd989449;
	}

	/* EDID CAP translation for HDMI 2.0 */
	stream->timing.flags.LTE_340MCSC_SCRAMBLE = dc_sink_data->edid_caps.lte_340mcsc_scramble;

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	memset(&stream->timing.dsc_cfg, 0, sizeof(stream->timing.dsc_cfg));
	stream->timing.dsc_cfg.num_slices_h = 0;
	stream->timing.dsc_cfg.num_slices_v = 0;
	stream->timing.dsc_cfg.bits_per_pixel = 128;
	stream->timing.dsc_cfg.block_pred_enable = 1;
	stream->timing.dsc_cfg.linebuf_depth = 9;
	stream->timing.dsc_cfg.version_minor = 2;
	stream->timing.dsc_cfg.ycbcr422_simple = 0;
#endif

	update_stream_signal(stream, dc_sink_data);

	stream->out_transfer_func = dc_create_transfer_func();
	stream->out_transfer_func->type = TF_TYPE_BYPASS;
	stream->out_transfer_func->ctx = stream->ctx;

	stream->stream_id = stream->ctx->dc_stream_id_count;
	stream->ctx->dc_stream_id_count++;
}