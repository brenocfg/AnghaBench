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
struct uio_pci_generic_dev {int /*<<< orphan*/  pdev; } ;
struct uio_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  pci_check_and_mask_intx (int /*<<< orphan*/ ) ; 
 struct uio_pci_generic_dev* to_uio_pci_generic_dev (struct uio_info*) ; 

__attribute__((used)) static irqreturn_t irqhandler(int irq, struct uio_info *info)
{
	struct uio_pci_generic_dev *gdev = to_uio_pci_generic_dev(info);

	if (!pci_check_and_mask_intx(gdev->pdev))
		return IRQ_NONE;

	/* UIO core will signal the user process. */
	return IRQ_HANDLED;
}