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
struct urb {int dummy; } ;
struct es2_ap_dev {int* cport_out_urb_busy; TYPE_1__* usb_dev; int /*<<< orphan*/  cport_out_urb_lock; struct urb** cport_out_urb; int /*<<< orphan*/ * cport_out_urb_cancelled; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NUM_CPORT_OUT_URB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *next_free_urb(struct es2_ap_dev *es2, gfp_t gfp_mask)
{
	struct urb *urb = NULL;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);

	/* Look in our pool of allocated urbs first, as that's the "fastest" */
	for (i = 0; i < NUM_CPORT_OUT_URB; ++i) {
		if (!es2->cport_out_urb_busy[i] &&
		    !es2->cport_out_urb_cancelled[i]) {
			es2->cport_out_urb_busy[i] = true;
			urb = es2->cport_out_urb[i];
			break;
		}
	}
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);
	if (urb)
		return urb;

	/*
	 * Crap, pool is empty, complain to the syslog and go allocate one
	 * dynamically as we have to succeed.
	 */
	dev_dbg(&es2->usb_dev->dev,
		"No free CPort OUT urbs, having to dynamically allocate one!\n");
	return usb_alloc_urb(0, gfp_mask);
}