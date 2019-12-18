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
struct zd_usb_interrupt {int /*<<< orphan*/  lock; int /*<<< orphan*/  read_regs_enabled; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_read_regs_int(struct zd_usb *usb)
{
	struct zd_usb_interrupt *intr = &usb->intr;

	spin_lock_irq(&intr->lock);
	atomic_set(&intr->read_regs_enabled, 0);
	spin_unlock_irq(&intr->lock);
}