#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  max_cll; int /*<<< orphan*/  max_fall; int /*<<< orphan*/  min_display_mastering_luminance; int /*<<< orphan*/  max_display_mastering_luminance; int /*<<< orphan*/  white_point; int /*<<< orphan*/  display_primaries; int /*<<< orphan*/  metadata_type; int /*<<< orphan*/  eotf; } ;
struct hdr_output_metadata {TYPE_4__ hdmi_metadata_type1; } ;
struct hdmi_drm_infoframe {int /*<<< orphan*/  max_cll; int /*<<< orphan*/  max_fall; int /*<<< orphan*/  min_display_mastering_luminance; int /*<<< orphan*/  max_display_mastering_luminance; int /*<<< orphan*/  white_point; int /*<<< orphan*/  display_primaries; int /*<<< orphan*/  metadata_type; int /*<<< orphan*/  eotf; } ;
struct drm_connector_state {TYPE_1__* hdr_output_metadata; struct drm_connector* connector; } ;
struct TYPE_6__ {int /*<<< orphan*/  eotf; } ;
struct TYPE_7__ {TYPE_2__ hdmi_type1; } ;
struct drm_connector {TYPE_3__ hdr_sink_metadata; } ;
struct TYPE_5__ {struct hdr_output_metadata* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 int hdmi_drm_infoframe_init (struct hdmi_drm_infoframe*) ; 
 int /*<<< orphan*/  is_eotf_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
drm_hdmi_infoframe_set_hdr_metadata(struct hdmi_drm_infoframe *frame,
				    const struct drm_connector_state *conn_state)
{
	struct drm_connector *connector;
	struct hdr_output_metadata *hdr_metadata;
	int err;

	if (!frame || !conn_state)
		return -EINVAL;

	connector = conn_state->connector;

	if (!conn_state->hdr_output_metadata)
		return -EINVAL;

	hdr_metadata = conn_state->hdr_output_metadata->data;

	if (!hdr_metadata || !connector)
		return -EINVAL;

	/* Sink EOTF is Bit map while infoframe is absolute values */
	if (!is_eotf_supported(hdr_metadata->hdmi_metadata_type1.eotf,
	    connector->hdr_sink_metadata.hdmi_type1.eotf)) {
		DRM_DEBUG_KMS("EOTF Not Supported\n");
		return -EINVAL;
	}

	err = hdmi_drm_infoframe_init(frame);
	if (err < 0)
		return err;

	frame->eotf = hdr_metadata->hdmi_metadata_type1.eotf;
	frame->metadata_type = hdr_metadata->hdmi_metadata_type1.metadata_type;

	BUILD_BUG_ON(sizeof(frame->display_primaries) !=
		     sizeof(hdr_metadata->hdmi_metadata_type1.display_primaries));
	BUILD_BUG_ON(sizeof(frame->white_point) !=
		     sizeof(hdr_metadata->hdmi_metadata_type1.white_point));

	memcpy(&frame->display_primaries,
	       &hdr_metadata->hdmi_metadata_type1.display_primaries,
	       sizeof(frame->display_primaries));

	memcpy(&frame->white_point,
	       &hdr_metadata->hdmi_metadata_type1.white_point,
	       sizeof(frame->white_point));

	frame->max_display_mastering_luminance =
		hdr_metadata->hdmi_metadata_type1.max_display_mastering_luminance;
	frame->min_display_mastering_luminance =
		hdr_metadata->hdmi_metadata_type1.min_display_mastering_luminance;
	frame->max_fall = hdr_metadata->hdmi_metadata_type1.max_fall;
	frame->max_cll = hdr_metadata->hdmi_metadata_type1.max_cll;

	return 0;
}