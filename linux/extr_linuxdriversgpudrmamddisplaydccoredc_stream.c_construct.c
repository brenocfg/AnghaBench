#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_20__ {int /*<<< orphan*/  link; } ;
struct TYPE_17__ {int /*<<< orphan*/  LTE_340MCSC_SCRAMBLE; } ;
struct TYPE_18__ {TYPE_6__ flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  all; } ;
struct TYPE_16__ {size_t mode_count; int* port_id; TYPE_4__ flags; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacture_id; int /*<<< orphan*/  display_name; int /*<<< orphan*/  video_latency; int /*<<< orphan*/  audio_latency; TYPE_2__* modes; } ;
struct dc_stream_state {TYPE_10__* out_transfer_func; struct dc_sink* sink; TYPE_9__ status; TYPE_7__ timing; TYPE_5__ audio_info; int /*<<< orphan*/  ctx; } ;
struct TYPE_19__ {size_t audio_mode_count; int /*<<< orphan*/  lte_340mcsc_scramble; int /*<<< orphan*/  speaker_flags; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacturer_id; int /*<<< orphan*/  display_name; int /*<<< orphan*/  video_latency; int /*<<< orphan*/  audio_latency; TYPE_3__* audio_modes; } ;
struct dc_sink {int /*<<< orphan*/  link; TYPE_8__ edid_caps; struct dc_container_id* dc_container_id; int /*<<< orphan*/  ctx; } ;
struct dc_container_id {int* portId; } ;
struct TYPE_14__ {int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format_code; int /*<<< orphan*/  channel_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  all; } ;
struct TYPE_13__ {int /*<<< orphan*/  sample_size; TYPE_1__ sample_rates; int /*<<< orphan*/  format_code; int /*<<< orphan*/  channel_count; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS ; 
 int /*<<< orphan*/  TF_TYPE_BYPASS ; 
 TYPE_10__* dc_create_transfer_func () ; 
 int /*<<< orphan*/  dc_sink_retain (struct dc_sink*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stream_signal (struct dc_stream_state*) ; 

__attribute__((used)) static void construct(struct dc_stream_state *stream,
	struct dc_sink *dc_sink_data)
{
	uint32_t i = 0;

	stream->sink = dc_sink_data;
	stream->ctx = stream->sink->ctx;

	dc_sink_retain(dc_sink_data);

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

	stream->status.link = stream->sink->link;

	update_stream_signal(stream);

	stream->out_transfer_func = dc_create_transfer_func();
	stream->out_transfer_func->type = TF_TYPE_BYPASS;
}