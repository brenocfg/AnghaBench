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
struct intel_encoder {int dummy; } ;
struct hdmi_spd_infoframe {int /*<<< orphan*/  sdi; } ;
struct TYPE_3__ {struct hdmi_spd_infoframe spd; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable; TYPE_1__ spd; } ;
struct intel_crtc_state {TYPE_2__ infoframes; int /*<<< orphan*/  has_infoframe; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_SPD ; 
 int /*<<< orphan*/  HDMI_SPD_SDI_PC ; 
 scalar_t__ WARN_ON (int) ; 
 int hdmi_spd_infoframe_check (struct hdmi_spd_infoframe*) ; 
 int hdmi_spd_infoframe_init (struct hdmi_spd_infoframe*,char*,char*) ; 
 int /*<<< orphan*/  intel_hdmi_infoframe_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_hdmi_compute_spd_infoframe(struct intel_encoder *encoder,
				 struct intel_crtc_state *crtc_state,
				 struct drm_connector_state *conn_state)
{
	struct hdmi_spd_infoframe *frame = &crtc_state->infoframes.spd.spd;
	int ret;

	if (!crtc_state->has_infoframe)
		return true;

	crtc_state->infoframes.enable |=
		intel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_SPD);

	ret = hdmi_spd_infoframe_init(frame, "Intel", "Integrated gfx");
	if (WARN_ON(ret))
		return false;

	frame->sdi = HDMI_SPD_SDI_PC;

	ret = hdmi_spd_infoframe_check(frame);
	if (WARN_ON(ret))
		return false;

	return true;
}