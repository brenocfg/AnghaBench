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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {TYPE_5__* ops; } ;
struct routing_scheme {int cnt; TYPE_2__* def; } ;
struct pvr2_hdw {int input_val; TYPE_1__* hdw_desc; scalar_t__ force_dirty; scalar_t__ input_dirty; } ;
typedef  enum cx25840_video_input { ____Placeholder_cx25840_video_input } cx25840_video_input ;
typedef  enum cx25840_audio_input { ____Placeholder_cx25840_audio_input } cx25840_audio_input ;
struct TYPE_10__ {TYPE_4__* audio; TYPE_3__* video; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* s_routing ) (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* s_routing ) (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int vid; int aud; } ;
struct TYPE_6__ {unsigned int signal_routing_scheme; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct routing_scheme**) ; 
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 struct routing_scheme** routing_schemes ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_cx25840_subdev_update(struct pvr2_hdw *hdw, struct v4l2_subdev *sd)
{
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev cx2584x update...");
	if (hdw->input_dirty || hdw->force_dirty) {
		enum cx25840_video_input vid_input;
		enum cx25840_audio_input aud_input;
		const struct routing_scheme *sp;
		unsigned int sid = hdw->hdw_desc->signal_routing_scheme;

		sp = (sid < ARRAY_SIZE(routing_schemes)) ?
			routing_schemes[sid] : NULL;
		if ((sp == NULL) ||
		    (hdw->input_val < 0) ||
		    (hdw->input_val >= sp->cnt)) {
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "*** WARNING *** subdev cx2584x set_input: Invalid routing scheme (%u) and/or input (%d)",
				   sid, hdw->input_val);
			return;
		}
		vid_input = sp->def[hdw->input_val].vid;
		aud_input = sp->def[hdw->input_val].aud;
		pvr2_trace(PVR2_TRACE_CHIPS,
			   "subdev cx2584x set_input vid=0x%x aud=0x%x",
			   vid_input, aud_input);
		sd->ops->video->s_routing(sd, (u32)vid_input, 0, 0);
		sd->ops->audio->s_routing(sd, (u32)aud_input, 0, 0);
	}
}