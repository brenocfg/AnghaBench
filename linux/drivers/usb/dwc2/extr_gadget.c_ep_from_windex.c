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
typedef  int u32 ;
struct dwc2_hsotg_ep {int dir_in; } ;
struct dwc2_hsotg {int num_of_eps; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 struct dwc2_hsotg_ep* index_to_ep (struct dwc2_hsotg*,int,int) ; 

__attribute__((used)) static struct dwc2_hsotg_ep *ep_from_windex(struct dwc2_hsotg *hsotg,
					    u32 windex)
{
	struct dwc2_hsotg_ep *ep;
	int dir = (windex & USB_DIR_IN) ? 1 : 0;
	int idx = windex & 0x7F;

	if (windex >= 0x100)
		return NULL;

	if (idx > hsotg->num_of_eps)
		return NULL;

	ep = index_to_ep(hsotg, idx, dir);

	if (idx && ep->dir_in != dir)
		return NULL;

	return ep;
}