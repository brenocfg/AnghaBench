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
struct pch_udc_ep {scalar_t__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_EPCTL_ADDR ; 
 int /*<<< orphan*/  UDC_EPCTL_F ; 
 int /*<<< orphan*/  UDC_EPCTL_S ; 
 int /*<<< orphan*/  pch_udc_ep_bit_set (struct pch_udc_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_udc_ep_set_stall(struct pch_udc_ep *ep)
{
	if (ep->in) {
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_F);
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	} else {
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	}
}