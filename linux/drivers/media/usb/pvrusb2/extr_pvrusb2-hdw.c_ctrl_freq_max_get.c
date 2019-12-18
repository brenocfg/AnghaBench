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
struct TYPE_2__ {unsigned long rangehigh; int capability; } ;
struct pvr2_hdw {TYPE_1__ tuner_signal_info; scalar_t__ tuner_signal_stale; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int TV_MAX_FREQ ; 
 int V4L2_TUNER_CAP_LOW ; 
 int /*<<< orphan*/  pvr2_hdw_status_poll (struct pvr2_hdw*) ; 

__attribute__((used)) static int ctrl_freq_max_get(struct pvr2_ctrl *cptr, int *vp)
{
	unsigned long fv;
	struct pvr2_hdw *hdw = cptr->hdw;
	if (hdw->tuner_signal_stale) {
		pvr2_hdw_status_poll(hdw);
	}
	fv = hdw->tuner_signal_info.rangehigh;
	if (!fv) {
		/* Safety fallback */
		*vp = TV_MAX_FREQ;
		return 0;
	}
	if (hdw->tuner_signal_info.capability & V4L2_TUNER_CAP_LOW) {
		fv = (fv * 125) / 2;
	} else {
		fv = fv * 62500;
	}
	*vp = fv;
	return 0;
}