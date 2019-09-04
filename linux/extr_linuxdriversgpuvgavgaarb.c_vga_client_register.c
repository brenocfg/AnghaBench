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
struct vga_device {void (* irq_set_state ) (void*,int) ;unsigned int (* set_vga_decode ) (void*,int) ;void* cookie; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_lock ; 
 struct vga_device* vgadev_find (struct pci_dev*) ; 

int vga_client_register(struct pci_dev *pdev, void *cookie,
			void (*irq_set_state)(void *cookie, bool state),
			unsigned int (*set_vga_decode)(void *cookie,
						       bool decode))
{
	int ret = -ENODEV;
	struct vga_device *vgadev;
	unsigned long flags;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	if (!vgadev)
		goto bail;

	vgadev->irq_set_state = irq_set_state;
	vgadev->set_vga_decode = set_vga_decode;
	vgadev->cookie = cookie;
	ret = 0;

bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	return ret;

}