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
struct vm_area_struct {struct usb_memory* vm_private_data; } ;
struct usb_memory {TYPE_1__* ps; int /*<<< orphan*/  vma_use_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void usbdev_vm_open(struct vm_area_struct *vma)
{
	struct usb_memory *usbm = vma->vm_private_data;
	unsigned long flags;

	spin_lock_irqsave(&usbm->ps->lock, flags);
	++usbm->vma_use_count;
	spin_unlock_irqrestore(&usbm->ps->lock, flags);
}