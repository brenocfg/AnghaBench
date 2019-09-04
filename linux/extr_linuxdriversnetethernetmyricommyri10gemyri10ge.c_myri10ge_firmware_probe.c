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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct myri10ge_priv {int tx_boundary; struct pci_dev* pdev; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOSYS ; 
 int /*<<< orphan*/  MXGEFW_CMD_UNALIGNED_TEST ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int myri10ge_dma_test (struct myri10ge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myri10ge_enable_ecrc (struct myri10ge_priv*) ; 
 int /*<<< orphan*/  myri10ge_fw_aligned ; 
 int /*<<< orphan*/  myri10ge_fw_unaligned ; 
 int myri10ge_load_firmware (struct myri10ge_priv*,int) ; 
 int pcie_get_readrq (struct pci_dev*) ; 
 int /*<<< orphan*/  set_fw_name (struct myri10ge_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void myri10ge_firmware_probe(struct myri10ge_priv *mgp)
{
	struct pci_dev *pdev = mgp->pdev;
	struct device *dev = &pdev->dev;
	int status;

	mgp->tx_boundary = 4096;
	/*
	 * Verify the max read request size was set to 4KB
	 * before trying the test with 4KB.
	 */
	status = pcie_get_readrq(pdev);
	if (status < 0) {
		dev_err(dev, "Couldn't read max read req size: %d\n", status);
		goto abort;
	}
	if (status != 4096) {
		dev_warn(dev, "Max Read Request size != 4096 (%d)\n", status);
		mgp->tx_boundary = 2048;
	}
	/*
	 * load the optimized firmware (which assumes aligned PCIe
	 * completions) in order to see if it works on this host.
	 */
	set_fw_name(mgp, myri10ge_fw_aligned, false);
	status = myri10ge_load_firmware(mgp, 1);
	if (status != 0) {
		goto abort;
	}

	/*
	 * Enable ECRC if possible
	 */
	myri10ge_enable_ecrc(mgp);

	/*
	 * Run a DMA test which watches for unaligned completions and
	 * aborts on the first one seen.
	 */

	status = myri10ge_dma_test(mgp, MXGEFW_CMD_UNALIGNED_TEST);
	if (status == 0)
		return;		/* keep the aligned firmware */

	if (status != -E2BIG)
		dev_warn(dev, "DMA test failed: %d\n", status);
	if (status == -ENOSYS)
		dev_warn(dev, "Falling back to ethp! "
			 "Please install up to date fw\n");
abort:
	/* fall back to using the unaligned firmware */
	mgp->tx_boundary = 2048;
	set_fw_name(mgp, myri10ge_fw_unaligned, false);
}