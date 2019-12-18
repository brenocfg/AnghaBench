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
struct zd_usb_interrupt {int /*<<< orphan*/  lock; struct urb* urb; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int usb_int_enabled(struct zd_usb *usb)
{
	unsigned long flags;
	struct zd_usb_interrupt *intr = &usb->intr;
	struct urb *urb;

	spin_lock_irqsave(&intr->lock, flags);
	urb = intr->urb;
	spin_unlock_irqrestore(&intr->lock, flags);
	return urb != NULL;
}