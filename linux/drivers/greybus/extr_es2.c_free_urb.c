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
struct urb {int dummy; } ;
struct es2_ap_dev {int* cport_out_urb_busy; int /*<<< orphan*/  cport_out_urb_lock; struct urb** cport_out_urb; } ;

/* Variables and functions */
 int NUM_CPORT_OUT_URB ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void free_urb(struct es2_ap_dev *es2, struct urb *urb)
{
	unsigned long flags;
	int i;
	/*
	 * See if this was an urb in our pool, if so mark it "free", otherwise
	 * we need to free it ourselves.
	 */
	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
	for (i = 0; i < NUM_CPORT_OUT_URB; ++i) {
		if (urb == es2->cport_out_urb[i]) {
			es2->cport_out_urb_busy[i] = false;
			urb = NULL;
			break;
		}
	}
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

	/* If urb is not NULL, then we need to free this urb */
	usb_free_urb(urb);
}