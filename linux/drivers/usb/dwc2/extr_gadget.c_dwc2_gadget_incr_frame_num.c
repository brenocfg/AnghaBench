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
struct dwc2_hsotg_ep {int frame_overrun; int /*<<< orphan*/  target_frame; scalar_t__ interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSTS_SOFFN_LIMIT ; 

__attribute__((used)) static inline void dwc2_gadget_incr_frame_num(struct dwc2_hsotg_ep *hs_ep)
{
	hs_ep->target_frame += hs_ep->interval;
	if (hs_ep->target_frame > DSTS_SOFFN_LIMIT) {
		hs_ep->frame_overrun = true;
		hs_ep->target_frame &= DSTS_SOFFN_LIMIT;
	} else {
		hs_ep->frame_overrun = false;
	}
}