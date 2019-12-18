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
struct usba_ep {int dummy; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_COUNT ; 
 int /*<<< orphan*/  STA ; 
 int USBA_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usba_ep* to_usba_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  usba_ep_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usba_ep_fifo_status(struct usb_ep *_ep)
{
	struct usba_ep *ep = to_usba_ep(_ep);

	return USBA_BFEXT(BYTE_COUNT, usba_ep_readl(ep, STA));
}