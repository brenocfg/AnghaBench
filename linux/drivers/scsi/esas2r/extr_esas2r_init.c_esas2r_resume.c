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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags2; int /*<<< orphan*/  intr_mode; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_IRQ_CLAIMED ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  esas2r_claim_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_debug (char*) ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_enable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_kickoff_timer (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_log_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ esas2r_map_regions (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_power_up (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  esas2r_setup_interrupts (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int esas2r_resume(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct esas2r_adapter *a = (struct esas2r_adapter *)host->hostdata;
	int rez;

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev), "resuming adapter()");
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_set_power_state(PCI_D0) "
		       "called");
	pci_set_power_state(pdev, PCI_D0);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_enable_wake(PCI_D0, 0) "
		       "called");
	pci_enable_wake(pdev, PCI_D0, 0);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_restore_state() called");
	pci_restore_state(pdev);
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pdev->dev),
		       "pci_enable_device() called");
	rez = pci_enable_device(pdev);
	pci_set_master(pdev);

	if (!a) {
		rez = -ENODEV;
		goto error_exit;
	}

	if (esas2r_map_regions(a) != 0) {
		esas2r_log(ESAS2R_LOG_CRIT, "could not re-map PCI regions!");
		rez = -ENOMEM;
		goto error_exit;
	}

	/* Set up interupt mode */
	esas2r_setup_interrupts(a, a->intr_mode);

	/*
	 * Disable chip interrupts to prevent spurious interrupts until we
	 * claim the IRQ.
	 */
	esas2r_disable_chip_interrupts(a);
	if (!esas2r_power_up(a, true)) {
		esas2r_debug("yikes, esas2r_power_up failed");
		rez = -ENOMEM;
		goto error_exit;
	}

	esas2r_claim_interrupts(a);

	if (test_bit(AF2_IRQ_CLAIMED, &a->flags2)) {
		/*
		 * Now that system interrupt(s) are claimed, we can enable
		 * chip interrupts.
		 */
		esas2r_enable_chip_interrupts(a);
		esas2r_kickoff_timer(a);
	} else {
		esas2r_debug("yikes, unable to claim IRQ");
		esas2r_log(ESAS2R_LOG_CRIT, "could not re-claim IRQ!");
		rez = -ENOMEM;
		goto error_exit;
	}

error_exit:
	esas2r_log_dev(ESAS2R_LOG_CRIT, &(pdev->dev), "esas2r_resume(): %d",
		       rez);
	return rez;
}