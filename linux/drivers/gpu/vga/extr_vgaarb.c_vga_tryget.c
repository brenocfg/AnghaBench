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
struct vga_device {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ __vga_tryget (struct vga_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_check_first_use () ; 
 struct pci_dev* vga_default_device () ; 
 int /*<<< orphan*/  vga_lock ; 
 struct vga_device* vgadev_find (struct pci_dev*) ; 

int vga_tryget(struct pci_dev *pdev, unsigned int rsrc)
{
	struct vga_device *vgadev;
	unsigned long flags;
	int rc = 0;

	vga_check_first_use();

	/* The one who calls us should check for this, but lets be sure... */
	if (pdev == NULL)
		pdev = vga_default_device();
	if (pdev == NULL)
		return 0;
	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NULL) {
		rc = -ENODEV;
		goto bail;
	}
	if (__vga_tryget(vgadev, rsrc))
		rc = -EBUSY;
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	return rc;
}