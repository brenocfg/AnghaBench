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
typedef  int u8 ;
struct pci_dev {int dev_flags; scalar_t__ imm_ready; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  PCIE_RESET_READY_POLL_MS ; 
 scalar_t__ PCI_AF_CAP ; 
 int PCI_AF_CAP_FLR ; 
 int PCI_AF_CAP_TP ; 
 scalar_t__ PCI_AF_CTRL ; 
 int /*<<< orphan*/  PCI_AF_CTRL_FLR ; 
 int PCI_AF_STATUS_TP ; 
 int /*<<< orphan*/  PCI_CAP_ID_AF ; 
 int PCI_DEV_FLAGS_NO_FLR_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pci_dev_wait (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_wait_for_pending (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_af_flr(struct pci_dev *dev, int probe)
{
	int pos;
	u8 cap;

	pos = pci_find_capability(dev, PCI_CAP_ID_AF);
	if (!pos)
		return -ENOTTY;

	if (dev->dev_flags & PCI_DEV_FLAGS_NO_FLR_RESET)
		return -ENOTTY;

	pci_read_config_byte(dev, pos + PCI_AF_CAP, &cap);
	if (!(cap & PCI_AF_CAP_TP) || !(cap & PCI_AF_CAP_FLR))
		return -ENOTTY;

	if (probe)
		return 0;

	/*
	 * Wait for Transaction Pending bit to clear.  A word-aligned test
	 * is used, so we use the control offset rather than status and shift
	 * the test bit to match.
	 */
	if (!pci_wait_for_pending(dev, pos + PCI_AF_CTRL,
				 PCI_AF_STATUS_TP << 8))
		pci_err(dev, "timed out waiting for pending transaction; performing AF function level reset anyway\n");

	pci_write_config_byte(dev, pos + PCI_AF_CTRL, PCI_AF_CTRL_FLR);

	if (dev->imm_ready)
		return 0;

	/*
	 * Per Advanced Capabilities for Conventional PCI ECN, 13 April 2006,
	 * updated 27 July 2006; a device must complete an FLR within
	 * 100ms, but may silently discard requests while the FLR is in
	 * progress.  Wait 100ms before trying to access the device.
	 */
	msleep(100);

	return pci_dev_wait(dev, "AF_FLR", PCIE_RESET_READY_POLL_MS);
}