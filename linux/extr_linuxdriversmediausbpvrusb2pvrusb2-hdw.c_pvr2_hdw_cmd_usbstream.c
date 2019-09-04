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
struct pvr2_hdw {scalar_t__ pathway_state; TYPE_1__* hdw_desc; } ;
struct TYPE_2__ {int digital_control_scheme; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FX2CMD_HCW_DTV_STREAMING_OFF ; 
 int /*<<< orphan*/  FX2CMD_HCW_DTV_STREAMING_ON ; 
 int /*<<< orphan*/  FX2CMD_STREAMING_OFF ; 
 int /*<<< orphan*/  FX2CMD_STREAMING_ON ; 
#define  PVR2_DIGITAL_SCHEME_HAUPPAUGE 129 
#define  PVR2_DIGITAL_SCHEME_ONAIR 128 
 scalar_t__ PVR2_PATHWAY_ANALOG ; 
 scalar_t__ PVR2_PATHWAY_DIGITAL ; 
 int pvr2_hdw_cmd_onair_digital_path_ctrl (struct pvr2_hdw*,int) ; 
 int pvr2_issue_simple_cmd (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_hdw_cmd_usbstream(struct pvr2_hdw *hdw,int runFl)
{
	int ret;

	/* If we're in analog mode, then just issue the usual analog
	   command. */
	if (hdw->pathway_state == PVR2_PATHWAY_ANALOG) {
		return pvr2_issue_simple_cmd(hdw,
					     (runFl ?
					      FX2CMD_STREAMING_ON :
					      FX2CMD_STREAMING_OFF));
		/*Note: Not reached */
	}

	if (hdw->pathway_state != PVR2_PATHWAY_DIGITAL) {
		/* Whoops, we don't know what mode we're in... */
		return -EINVAL;
	}

	/* To get here we have to be in digital mode.  The mechanism here
	   is unfortunately different for different vendors.  So we switch
	   on the device's digital scheme attribute in order to figure out
	   what to do. */
	switch (hdw->hdw_desc->digital_control_scheme) {
	case PVR2_DIGITAL_SCHEME_HAUPPAUGE:
		return pvr2_issue_simple_cmd(hdw,
					     (runFl ?
					      FX2CMD_HCW_DTV_STREAMING_ON :
					      FX2CMD_HCW_DTV_STREAMING_OFF));
	case PVR2_DIGITAL_SCHEME_ONAIR:
		ret = pvr2_issue_simple_cmd(hdw,
					    (runFl ?
					     FX2CMD_STREAMING_ON :
					     FX2CMD_STREAMING_OFF));
		if (ret) return ret;
		return pvr2_hdw_cmd_onair_digital_path_ctrl(hdw,runFl);
	default:
		return -EINVAL;
	}
}