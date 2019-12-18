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
struct pvr2_hdw {unsigned int* freqTable; int freqSlotRadio; int freqSlotTelevision; scalar_t__ freqSelector; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int FREQTABLE_SIZE ; 
 int /*<<< orphan*/  pvr2_hdw_set_cur_freq (struct pvr2_hdw*,unsigned int) ; 

__attribute__((used)) static int ctrl_channel_set(struct pvr2_ctrl *cptr,int m,int slotId)
{
	unsigned freq = 0;
	struct pvr2_hdw *hdw = cptr->hdw;
	if ((slotId < 0) || (slotId > FREQTABLE_SIZE)) return 0;
	if (slotId > 0) {
		freq = hdw->freqTable[slotId-1];
		if (!freq) return 0;
		pvr2_hdw_set_cur_freq(hdw,freq);
	}
	if (hdw->freqSelector) {
		hdw->freqSlotRadio = slotId;
	} else {
		hdw->freqSlotTelevision = slotId;
	}
	return 0;
}