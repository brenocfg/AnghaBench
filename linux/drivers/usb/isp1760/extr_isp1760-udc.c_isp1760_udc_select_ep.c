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
struct isp1760_ep {int addr; } ;

/* Variables and functions */
 int USB_ENDPOINT_DIR_MASK ; 
 int /*<<< orphan*/  __isp1760_udc_select_ep (struct isp1760_ep*,int) ; 

__attribute__((used)) static void isp1760_udc_select_ep(struct isp1760_ep *ep)
{
	__isp1760_udc_select_ep(ep, ep->addr & USB_ENDPOINT_DIR_MASK);
}