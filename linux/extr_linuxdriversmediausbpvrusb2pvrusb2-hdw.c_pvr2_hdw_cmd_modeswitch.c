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
struct pvr2_hdw {int pathway_state; TYPE_1__* hdw_desc; } ;
struct TYPE_2__ {int digital_control_scheme; } ;

/* Variables and functions */
#define  PVR2_DIGITAL_SCHEME_HAUPPAUGE 129 
#define  PVR2_DIGITAL_SCHEME_ONAIR 128 
 int PVR2_PATHWAY_ANALOG ; 
 int PVR2_PATHWAY_DIGITAL ; 
 int /*<<< orphan*/  pvr2_hdw_cmd_decoder_reset (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_cmd_hcw_demod_reset (struct pvr2_hdw*,int) ; 
 int /*<<< orphan*/  pvr2_hdw_cmd_onair_fe_power_ctrl (struct pvr2_hdw*,int) ; 
 int /*<<< orphan*/  pvr2_hdw_untrip_unlocked (struct pvr2_hdw*) ; 

__attribute__((used)) static void pvr2_hdw_cmd_modeswitch(struct pvr2_hdw *hdw,int digitalFl)
{
	int cmode;
	/* Compare digital/analog desired setting with current setting.  If
	   they don't match, fix it... */
	cmode = (digitalFl ? PVR2_PATHWAY_DIGITAL : PVR2_PATHWAY_ANALOG);
	if (cmode == hdw->pathway_state) {
		/* They match; nothing to do */
		return;
	}

	switch (hdw->hdw_desc->digital_control_scheme) {
	case PVR2_DIGITAL_SCHEME_HAUPPAUGE:
		pvr2_hdw_cmd_hcw_demod_reset(hdw,digitalFl);
		if (cmode == PVR2_PATHWAY_ANALOG) {
			/* If moving to analog mode, also force the decoder
			   to reset.  If no decoder is attached, then it's
			   ok to ignore this because if/when the decoder
			   attaches, it will reset itself at that time. */
			pvr2_hdw_cmd_decoder_reset(hdw);
		}
		break;
	case PVR2_DIGITAL_SCHEME_ONAIR:
		/* Supposedly we should always have the power on whether in
		   digital or analog mode.  But for now do what appears to
		   work... */
		pvr2_hdw_cmd_onair_fe_power_ctrl(hdw,digitalFl);
		break;
	default: break;
	}

	pvr2_hdw_untrip_unlocked(hdw);
	hdw->pathway_state = cmode;
}