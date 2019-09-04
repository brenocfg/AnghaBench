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
struct pvr2_hdw {int freqProgSlot; int* freqTable; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int FREQTABLE_SIZE ; 

__attribute__((used)) static int ctrl_channelfreq_get(struct pvr2_ctrl *cptr,int *vp)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	if ((hdw->freqProgSlot > 0) && (hdw->freqProgSlot <= FREQTABLE_SIZE)) {
		*vp = hdw->freqTable[hdw->freqProgSlot-1];
	} else {
		*vp = 0;
	}
	return 0;
}