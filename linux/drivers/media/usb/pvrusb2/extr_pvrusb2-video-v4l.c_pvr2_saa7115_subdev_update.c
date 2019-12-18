#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {TYPE_3__* ops; } ;
struct routing_scheme {size_t cnt; int /*<<< orphan*/ * def; } ;
struct pvr2_hdw {size_t input_val; TYPE_1__* hdw_desc; scalar_t__ force_dirty; scalar_t__ input_dirty; } ;
struct TYPE_6__ {TYPE_2__* video; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* s_routing ) (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {unsigned int signal_routing_scheme; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct routing_scheme**) ; 
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 struct routing_scheme** routing_schemes ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_saa7115_subdev_update(struct pvr2_hdw *hdw, struct v4l2_subdev *sd)
{
	if (hdw->input_dirty || hdw->force_dirty) {
		const struct routing_scheme *sp;
		unsigned int sid = hdw->hdw_desc->signal_routing_scheme;
		u32 input;

		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_input(%d)",
			   hdw->input_val);

		sp = (sid < ARRAY_SIZE(routing_schemes)) ?
			routing_schemes[sid] : NULL;
		if ((sp == NULL) ||
		    (hdw->input_val < 0) ||
		    (hdw->input_val >= sp->cnt)) {
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "*** WARNING *** subdev v4l2 set_input: Invalid routing scheme (%u) and/or input (%d)",
				   sid, hdw->input_val);
			return;
		}
		input = sp->def[hdw->input_val];
		sd->ops->video->s_routing(sd, input, 0, 0);
	}
}