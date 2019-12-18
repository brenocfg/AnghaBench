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
typedef  int u8 ;
typedef  int u32 ;
struct dwc3_trb {int ctrl; } ;
struct dwc3_ep {scalar_t__ trb_enqueue; scalar_t__ trb_dequeue; } ;

/* Variables and functions */
 int DWC3_TRB_CTRL_HWO ; 
 int DWC3_TRB_NUM ; 
 struct dwc3_trb* dwc3_ep_prev_trb (struct dwc3_ep*,scalar_t__) ; 

__attribute__((used)) static u32 dwc3_calc_trbs_left(struct dwc3_ep *dep)
{
	struct dwc3_trb		*tmp;
	u8			trbs_left;

	/*
	 * If enqueue & dequeue are equal than it is either full or empty.
	 *
	 * One way to know for sure is if the TRB right before us has HWO bit
	 * set or not. If it has, then we're definitely full and can't fit any
	 * more transfers in our ring.
	 */
	if (dep->trb_enqueue == dep->trb_dequeue) {
		tmp = dwc3_ep_prev_trb(dep, dep->trb_enqueue);
		if (tmp->ctrl & DWC3_TRB_CTRL_HWO)
			return 0;

		return DWC3_TRB_NUM - 1;
	}

	trbs_left = dep->trb_dequeue - dep->trb_enqueue;
	trbs_left &= (DWC3_TRB_NUM - 1);

	if (dep->trb_dequeue < dep->trb_enqueue)
		trbs_left--;

	return trbs_left;
}