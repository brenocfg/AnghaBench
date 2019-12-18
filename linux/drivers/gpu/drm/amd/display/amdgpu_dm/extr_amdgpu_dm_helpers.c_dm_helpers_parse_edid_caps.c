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
struct cea_sad {int /*<<< orphan*/  byte2; int /*<<< orphan*/  freq; scalar_t__ channels; int /*<<< orphan*/  format; } ;
typedef  struct cea_sad uint8_t ;
typedef  int uint16_t ;
struct edid {TYPE_5__* detailed_timings; int /*<<< orphan*/  mfg_year; int /*<<< orphan*/  mfg_week; int /*<<< orphan*/  serial; scalar_t__* prod_code; scalar_t__* mfg_id; } ;
struct dc_edid_caps {int manufacturer_id; int product_id; char* display_name; int audio_mode_count; struct cea_sad speaker_flags; TYPE_6__* audio_modes; int /*<<< orphan*/  edid_hdmi; int /*<<< orphan*/  manufacture_year; int /*<<< orphan*/  manufacture_week; int /*<<< orphan*/  serial_number; } ;
struct dc_edid {scalar_t__ raw_edid; } ;
struct dc_context {int dummy; } ;
typedef  enum dc_edid_status { ____Placeholder_dc_edid_status } dc_edid_status ;
struct TYPE_12__ {int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_rate; scalar_t__ channel_count; int /*<<< orphan*/  format_code; } ;
struct TYPE_7__ {char* str; } ;
struct TYPE_8__ {TYPE_1__ str; } ;
struct TYPE_9__ {int type; TYPE_2__ data; } ;
struct TYPE_10__ {TYPE_3__ other_data; } ;
struct TYPE_11__ {TYPE_4__ data; } ;

/* Variables and functions */
 int DC_MAX_AUDIO_DESC_COUNT ; 
 struct cea_sad DEFAULT_SPEAKER_LOCATION ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int EDID_BAD_CHECKSUM ; 
 int EDID_BAD_INPUT ; 
 int EDID_OK ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (struct edid*) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 int drm_edid_to_sad (struct edid*,struct cea_sad**) ; 
 int drm_edid_to_speaker_allocation (struct edid*,struct cea_sad**) ; 
 int /*<<< orphan*/  kfree (struct cea_sad*) ; 

enum dc_edid_status dm_helpers_parse_edid_caps(
		struct dc_context *ctx,
		const struct dc_edid *edid,
		struct dc_edid_caps *edid_caps)
{
	struct edid *edid_buf = (struct edid *) edid->raw_edid;
	struct cea_sad *sads;
	int sad_count = -1;
	int sadb_count = -1;
	int i = 0;
	int j = 0;
	uint8_t *sadb = NULL;

	enum dc_edid_status result = EDID_OK;

	if (!edid_caps || !edid)
		return EDID_BAD_INPUT;

	if (!drm_edid_is_valid(edid_buf))
		result = EDID_BAD_CHECKSUM;

	edid_caps->manufacturer_id = (uint16_t) edid_buf->mfg_id[0] |
					((uint16_t) edid_buf->mfg_id[1])<<8;
	edid_caps->product_id = (uint16_t) edid_buf->prod_code[0] |
					((uint16_t) edid_buf->prod_code[1])<<8;
	edid_caps->serial_number = edid_buf->serial;
	edid_caps->manufacture_week = edid_buf->mfg_week;
	edid_caps->manufacture_year = edid_buf->mfg_year;

	/* One of the four detailed_timings stores the monitor name. It's
	 * stored in an array of length 13. */
	for (i = 0; i < 4; i++) {
		if (edid_buf->detailed_timings[i].data.other_data.type == 0xfc) {
			while (j < 13 && edid_buf->detailed_timings[i].data.other_data.data.str.str[j]) {
				if (edid_buf->detailed_timings[i].data.other_data.data.str.str[j] == '\n')
					break;

				edid_caps->display_name[j] =
					edid_buf->detailed_timings[i].data.other_data.data.str.str[j];
				j++;
			}
		}
	}

	edid_caps->edid_hdmi = drm_detect_hdmi_monitor(
			(struct edid *) edid->raw_edid);

	sad_count = drm_edid_to_sad((struct edid *) edid->raw_edid, &sads);
	if (sad_count <= 0) {
		DRM_INFO("SADs count is: %d, don't need to read it\n",
				sad_count);
		return result;
	}

	edid_caps->audio_mode_count = sad_count < DC_MAX_AUDIO_DESC_COUNT ? sad_count : DC_MAX_AUDIO_DESC_COUNT;
	for (i = 0; i < edid_caps->audio_mode_count; ++i) {
		struct cea_sad *sad = &sads[i];

		edid_caps->audio_modes[i].format_code = sad->format;
		edid_caps->audio_modes[i].channel_count = sad->channels + 1;
		edid_caps->audio_modes[i].sample_rate = sad->freq;
		edid_caps->audio_modes[i].sample_size = sad->byte2;
	}

	sadb_count = drm_edid_to_speaker_allocation((struct edid *) edid->raw_edid, &sadb);

	if (sadb_count < 0) {
		DRM_ERROR("Couldn't read Speaker Allocation Data Block: %d\n", sadb_count);
		sadb_count = 0;
	}

	if (sadb_count)
		edid_caps->speaker_flags = sadb[0];
	else
		edid_caps->speaker_flags = DEFAULT_SPEAKER_LOCATION;

	kfree(sads);
	kfree(sadb);

	return result;
}