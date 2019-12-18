#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
union hdmi_infoframe {TYPE_1__ any; } ;
typedef  int /*<<< orphan*/  u8 ;
struct intel_sdvo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable; union hdmi_infoframe avi; } ;
struct intel_crtc_state {TYPE_2__ infoframes; int /*<<< orphan*/  has_hdmi_sink; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sdvo_data ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  SDVO_HBUF_INDEX_AVI_IF ; 
 int hdmi_infoframe_unpack (union hdmi_infoframe*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  intel_hdmi_infoframe_enable (scalar_t__) ; 
 scalar_t__ intel_sdvo_read_infoframe (struct intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void intel_sdvo_get_avi_infoframe(struct intel_sdvo *intel_sdvo,
					 struct intel_crtc_state *crtc_state)
{
	u8 sdvo_data[HDMI_INFOFRAME_SIZE(AVI)];
	union hdmi_infoframe *frame = &crtc_state->infoframes.avi;
	ssize_t len;
	int ret;

	if (!crtc_state->has_hdmi_sink)
		return;

	len = intel_sdvo_read_infoframe(intel_sdvo, SDVO_HBUF_INDEX_AVI_IF,
					sdvo_data, sizeof(sdvo_data));
	if (len < 0) {
		DRM_DEBUG_KMS("failed to read AVI infoframe\n");
		return;
	} else if (len == 0) {
		return;
	}

	crtc_state->infoframes.enable |=
		intel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI);

	ret = hdmi_infoframe_unpack(frame, sdvo_data, len);
	if (ret) {
		DRM_DEBUG_KMS("Failed to unpack AVI infoframe\n");
		return;
	}

	if (frame->any.type != HDMI_INFOFRAME_TYPE_AVI)
		DRM_DEBUG_KMS("Found the wrong infoframe type 0x%x (expected 0x%02x)\n",
			      frame->any.type, HDMI_INFOFRAME_TYPE_AVI);
}