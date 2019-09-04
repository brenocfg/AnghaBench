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
typedef  int u32 ;
struct v4l2_subdev {TYPE_2__* ops; } ;
struct pvr2_hdw {int input_val; scalar_t__ force_dirty; scalar_t__ input_dirty; } ;
struct TYPE_4__ {TYPE_1__* audio; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* s_routing ) (struct v4l2_subdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  PVR2_CVAL_INPUT_RADIO 128 
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_wm8775_subdev_update(struct pvr2_hdw *hdw, struct v4l2_subdev *sd)
{
	if (hdw->input_dirty || hdw->force_dirty) {
		u32 input;

		switch (hdw->input_val) {
		case PVR2_CVAL_INPUT_RADIO:
			input = 1;
			break;
		default:
			/* All other cases just use the second input */
			input = 2;
			break;
		}
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev wm8775 set_input(val=%d route=0x%x)",
			   hdw->input_val, input);

		sd->ops->audio->s_routing(sd, input, 0, 0);
	}
}