#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvr2_hdw {int flag_decoder_missed; scalar_t__ decoder_client_id; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pvr2_decoder_enable(struct pvr2_hdw *hdw,int enablefl)
{
	/* Even though we really only care about the video decoder chip at
	   this point, we'll broadcast stream on/off to all sub-devices
	   anyway, just in case somebody else wants to hear the
	   command... */
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 stream=%s",
		   (enablefl ? "on" : "off"));
	v4l2_device_call_all(&hdw->v4l2_dev, 0, video, s_stream, enablefl);
	v4l2_device_call_all(&hdw->v4l2_dev, 0, audio, s_stream, enablefl);
	if (hdw->decoder_client_id) {
		/* We get here if the encoder has been noticed.  Otherwise
		   we'll issue a warning to the user (which should
		   normally never happen). */
		return 0;
	}
	if (!hdw->flag_decoder_missed) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "WARNING: No decoder present");
		hdw->flag_decoder_missed = !0;
		trace_stbit("flag_decoder_missed",
			    hdw->flag_decoder_missed);
	}
	return -EIO;
}