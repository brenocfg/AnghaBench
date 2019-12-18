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
struct pvr2_hdw {unsigned int freqProgSlot; int* freqTable; unsigned int freqSlotRadio; unsigned int freqSlotTelevision; scalar_t__ freqSelector; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 unsigned int FREQTABLE_SIZE ; 

__attribute__((used)) static int ctrl_channelfreq_set(struct pvr2_ctrl *cptr,int m,int v)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	unsigned int slotId = hdw->freqProgSlot;
	if ((slotId > 0) && (slotId <= FREQTABLE_SIZE)) {
		hdw->freqTable[slotId-1] = v;
		/* Handle side effects correctly - if we're tuned to this
		   slot, then forgot the slot id relation since the stored
		   frequency has been changed. */
		if (hdw->freqSelector) {
			if (hdw->freqSlotRadio == slotId) {
				hdw->freqSlotRadio = 0;
			}
		} else {
			if (hdw->freqSlotTelevision == slotId) {
				hdw->freqSlotTelevision = 0;
			}
		}
	}
	return 0;
}