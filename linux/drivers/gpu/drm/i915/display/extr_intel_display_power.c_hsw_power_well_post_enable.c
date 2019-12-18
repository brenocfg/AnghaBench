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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_MSR_READ ; 
 int /*<<< orphan*/  VGA_MSR_WRITE ; 
 int /*<<< orphan*/  VGA_RSRC_LEGACY_IO ; 
 int /*<<< orphan*/  gen8_irq_power_well_post_enable (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_get_uninterruptible (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_put (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_power_well_post_enable(struct drm_i915_private *dev_priv,
				       u8 irq_pipe_mask, bool has_vga)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;

	/*
	 * After we re-enable the power well, if we touch VGA register 0x3d5
	 * we'll get unclaimed register interrupts. This stops after we write
	 * anything to the VGA MSR register. The vgacon module uses this
	 * register all the time, so if we unbind our driver and, as a
	 * consequence, bind vgacon, we'll get stuck in an infinite loop at
	 * console_unlock(). So make here we touch the VGA MSR register, making
	 * sure vgacon can keep working normally without triggering interrupts
	 * and error messages.
	 */
	if (has_vga) {
		vga_get_uninterruptible(pdev, VGA_RSRC_LEGACY_IO);
		outb(inb(VGA_MSR_READ), VGA_MSR_WRITE);
		vga_put(pdev, VGA_RSRC_LEGACY_IO);
	}

	if (irq_pipe_mask)
		gen8_irq_power_well_post_enable(dev_priv, irq_pipe_mask);
}