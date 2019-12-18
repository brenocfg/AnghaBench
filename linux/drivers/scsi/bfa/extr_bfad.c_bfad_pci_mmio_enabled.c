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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int /*<<< orphan*/  hal_tmo; int /*<<< orphan*/  comp; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; TYPE_1__ bfa; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  bfa_fcs_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_ioc_debug_save_ftrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfad_remove_intr (struct bfad_s*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct bfad_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t
bfad_pci_mmio_enabled(struct pci_dev *pdev)
{
	unsigned long	flags;
	struct bfad_s *bfad = pci_get_drvdata(pdev);

	dev_printk(KERN_INFO, &pdev->dev, "mmio_enabled\n");

	/* Fetch FW diagnostic information */
	bfa_ioc_debug_save_ftrc(&bfad->bfa.ioc);

	/* Cancel all pending IOs */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfa_fcs_stop(&bfad->bfa_fcs);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	wait_for_completion(&bfad->comp);

	bfad_remove_intr(bfad);
	del_timer_sync(&bfad->hal_tmo);
	pci_disable_device(pdev);

	return PCI_ERS_RESULT_NEED_RESET;
}