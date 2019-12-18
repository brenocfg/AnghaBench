#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cea_rev; } ;
struct drm_connector {int /*<<< orphan*/ * audio_latency; int /*<<< orphan*/ * video_latency; scalar_t__* latency_present; TYPE_1__ display_info; } ;
struct dc_edid_caps {int audio_mode_count; int /*<<< orphan*/  speaker_flags; TYPE_4__* audio_modes; int /*<<< orphan*/  display_name; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacturer_id; } ;
struct dc_sink {struct dc_edid_caps edid_caps; } ;
struct TYPE_10__ {int /*<<< orphan*/  all; } ;
struct audio_info {int mode_count; int /*<<< orphan*/  audio_latency; int /*<<< orphan*/  video_latency; TYPE_5__ flags; TYPE_3__* modes; int /*<<< orphan*/  display_name; int /*<<< orphan*/  product_id; int /*<<< orphan*/  manufacture_id; } ;
typedef  enum audio_format_code { ____Placeholder_audio_format_code } audio_format_code ;
struct TYPE_9__ {int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_count; scalar_t__ format_code; } ;
struct TYPE_7__ {int /*<<< orphan*/  all; } ;
struct TYPE_8__ {int format_code; int /*<<< orphan*/  sample_size; TYPE_2__ sample_rates; int /*<<< orphan*/  channel_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_audio_info(struct audio_info *audio_info,
			    const struct drm_connector *drm_connector,
			    const struct dc_sink *dc_sink)
{
	int i = 0;
	int cea_revision = 0;
	const struct dc_edid_caps *edid_caps = &dc_sink->edid_caps;

	audio_info->manufacture_id = edid_caps->manufacturer_id;
	audio_info->product_id = edid_caps->product_id;

	cea_revision = drm_connector->display_info.cea_rev;

	strscpy(audio_info->display_name,
		edid_caps->display_name,
		AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS);

	if (cea_revision >= 3) {
		audio_info->mode_count = edid_caps->audio_mode_count;

		for (i = 0; i < audio_info->mode_count; ++i) {
			audio_info->modes[i].format_code =
					(enum audio_format_code)
					(edid_caps->audio_modes[i].format_code);
			audio_info->modes[i].channel_count =
					edid_caps->audio_modes[i].channel_count;
			audio_info->modes[i].sample_rates.all =
					edid_caps->audio_modes[i].sample_rate;
			audio_info->modes[i].sample_size =
					edid_caps->audio_modes[i].sample_size;
		}
	}

	audio_info->flags.all = edid_caps->speaker_flags;

	/* TODO: We only check for the progressive mode, check for interlace mode too */
	if (drm_connector->latency_present[0]) {
		audio_info->video_latency = drm_connector->video_latency[0];
		audio_info->audio_latency = drm_connector->audio_latency[0];
	}

	/* TODO: For DP, video and audio latency should be calculated from DPCD caps */

}