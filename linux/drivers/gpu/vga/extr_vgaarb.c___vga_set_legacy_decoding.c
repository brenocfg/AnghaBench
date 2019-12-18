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
struct vga_device {scalar_t__ set_vga_decode; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned int VGA_RSRC_LEGACY_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_lock ; 
 int /*<<< orphan*/  vga_update_device_decodes (struct vga_device*,unsigned int) ; 
 struct vga_device* vgadev_find (struct pci_dev*) ; 

__attribute__((used)) static void __vga_set_legacy_decoding(struct pci_dev *pdev,
				      unsigned int decodes,
				      bool userspace)
{
	struct vga_device *vgadev;
	unsigned long flags;

	decodes &= VGA_RSRC_LEGACY_MASK;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NULL)
		goto bail;

	/* don't let userspace futz with kernel driver decodes */
	if (userspace && vgadev->set_vga_decode)
		goto bail;

	/* update the device decodes + counter */
	vga_update_device_decodes(vgadev, decodes);

	/* XXX if somebody is going from "doesn't decode" to "decodes" state
	 * here, additional care must be taken as we may have pending owner
	 * ship of non-legacy region ...
	 */
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
}