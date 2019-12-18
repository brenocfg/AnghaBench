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
struct pci230_private {unsigned char* res_owned; int /*<<< orphan*/  res_spinlock; } ;
struct comedi_device {struct pci230_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pci230_release_shared(struct comedi_device *dev,
				  unsigned char res_mask, unsigned int owner)
{
	struct pci230_private *devpriv = dev->private;
	unsigned long irqflags;

	spin_lock_irqsave(&devpriv->res_spinlock, irqflags);
	devpriv->res_owned[owner] &= ~res_mask;
	spin_unlock_irqrestore(&devpriv->res_spinlock, irqflags);
}