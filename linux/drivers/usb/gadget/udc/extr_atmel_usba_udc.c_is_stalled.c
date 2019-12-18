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
struct usba_udc {int dummy; } ;
struct usba_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STA ; 
 int USBA_FORCE_STALL ; 
 int usba_ep_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_stalled(struct usba_udc *udc, struct usba_ep *ep)
{
	if (usba_ep_readl(ep, STA) & USBA_FORCE_STALL)
		return 1;
	return 0;
}