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
struct pvr2_hdw {int input_val; int input_dirty; int freqSelector; int freqDirty; } ;

/* Variables and functions */
 int PVR2_CVAL_INPUT_DTV ; 
 int PVR2_CVAL_INPUT_RADIO ; 
 int PVR2_CVAL_INPUT_TV ; 

__attribute__((used)) static int pvr2_hdw_set_input(struct pvr2_hdw *hdw,int v)
{
	if (hdw->input_val != v) {
		hdw->input_val = v;
		hdw->input_dirty = !0;
	}

	/* Handle side effects - if we switch to a mode that needs the RF
	   tuner, then select the right frequency choice as well and mark
	   it dirty. */
	if (hdw->input_val == PVR2_CVAL_INPUT_RADIO) {
		hdw->freqSelector = 0;
		hdw->freqDirty = !0;
	} else if ((hdw->input_val == PVR2_CVAL_INPUT_TV) ||
		   (hdw->input_val == PVR2_CVAL_INPUT_DTV)) {
		hdw->freqSelector = 1;
		hdw->freqDirty = !0;
	}
	return 0;
}