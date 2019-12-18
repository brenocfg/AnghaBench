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
struct dwc2_hsotg_ep {scalar_t__ target_frame; } ;

/* Variables and functions */
 scalar_t__ DSTS_SOFFN_LIMIT ; 

__attribute__((used)) static inline void dwc2_gadget_dec_frame_num_by_one(struct dwc2_hsotg_ep *hs_ep)
{
	if (hs_ep->target_frame)
		hs_ep->target_frame -= 1;
	else
		hs_ep->target_frame = DSTS_SOFFN_LIMIT;
}