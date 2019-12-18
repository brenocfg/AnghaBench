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
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ep_list; } ;
struct dwc3_ep {TYPE_1__ endpoint; } ;
struct dwc3 {struct dwc3_ep** eps; } ;

/* Variables and functions */
 size_t DWC3_ENDPOINTS_NUM ; 
 int /*<<< orphan*/  dwc3_free_trb_pool (struct dwc3_ep*) ; 
 int /*<<< orphan*/  kfree (struct dwc3_ep*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_gadget_free_endpoints(struct dwc3 *dwc)
{
	struct dwc3_ep			*dep;
	u8				epnum;

	for (epnum = 0; epnum < DWC3_ENDPOINTS_NUM; epnum++) {
		dep = dwc->eps[epnum];
		if (!dep)
			continue;
		/*
		 * Physical endpoints 0 and 1 are special; they form the
		 * bi-directional USB endpoint 0.
		 *
		 * For those two physical endpoints, we don't allocate a TRB
		 * pool nor do we add them the endpoints list. Due to that, we
		 * shouldn't do these two operations otherwise we would end up
		 * with all sorts of bugs when removing dwc3.ko.
		 */
		if (epnum != 0 && epnum != 1) {
			dwc3_free_trb_pool(dep);
			list_del(&dep->endpoint.ep_list);
		}

		kfree(dep);
	}
}