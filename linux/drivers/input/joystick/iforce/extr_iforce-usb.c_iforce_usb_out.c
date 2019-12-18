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
struct urb {int /*<<< orphan*/  status; struct iforce_usb* context; } ;
struct iforce {int /*<<< orphan*/  wait; int /*<<< orphan*/  xmit_flags; } ;
struct iforce_usb {TYPE_1__* intf; struct iforce iforce; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFORCE_XMIT_RUNNING ; 
 int /*<<< orphan*/  __iforce_usb_xmit (struct iforce*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_out(struct urb *urb)
{
	struct iforce_usb *iforce_usb = urb->context;
	struct iforce *iforce = &iforce_usb->iforce;

	if (urb->status) {
		clear_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags);
		dev_dbg(&iforce_usb->intf->dev, "urb->status %d, exiting\n",
			urb->status);
		return;
	}

	__iforce_usb_xmit(iforce);

	wake_up(&iforce->wait);
}