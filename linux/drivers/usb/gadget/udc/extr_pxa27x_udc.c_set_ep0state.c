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
struct pxa_udc {int ep0state; struct pxa_ep* pxa_ep; } ;
struct pxa_ep {int dummy; } ;

/* Variables and functions */
 char* EP0_STNAME (struct pxa_udc*) ; 
 int /*<<< orphan*/  UDCBCR ; 
 int /*<<< orphan*/  UDCCSR ; 
 int /*<<< orphan*/  ep_dbg (struct pxa_ep*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_ep_readl (struct pxa_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ep0state(struct pxa_udc *udc, int state)
{
	struct pxa_ep *ep = &udc->pxa_ep[0];
	char *old_stname = EP0_STNAME(udc);

	udc->ep0state = state;
	ep_dbg(ep, "state=%s->%s, udccsr0=0x%03x, udcbcr=%d\n", old_stname,
		EP0_STNAME(udc), udc_ep_readl(ep, UDCCSR),
		udc_ep_readl(ep, UDCBCR));
}