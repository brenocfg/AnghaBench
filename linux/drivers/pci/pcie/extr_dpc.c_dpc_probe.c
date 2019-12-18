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
typedef  int u16 ;
struct device {int dummy; } ;
struct pcie_device {int /*<<< orphan*/  irq; struct device device; struct pci_dev* port; } ;
struct pci_dev {int dummy; } ;
struct dpc_dev {int rp_extensions; int rp_log_size; scalar_t__ cap_pos; struct pcie_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  FLAG (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ PCI_EXP_DPC_CAP ; 
 int PCI_EXP_DPC_CAP_DL_ACTIVE ; 
 int PCI_EXP_DPC_CAP_POISONED_TLP ; 
 int PCI_EXP_DPC_CAP_RP_EXT ; 
 int PCI_EXP_DPC_CAP_SW_TRIGGER ; 
 scalar_t__ PCI_EXP_DPC_CTL ; 
 int PCI_EXP_DPC_CTL_EN_FATAL ; 
 int PCI_EXP_DPC_CTL_INT_EN ; 
 int PCI_EXP_DPC_IRQ ; 
 int PCI_EXP_DPC_RP_PIO_LOG_SIZE ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_DPC ; 
 struct dpc_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dpc_dev*) ; 
 int /*<<< orphan*/  dpc_handler ; 
 int /*<<< orphan*/  dpc_irq ; 
 int /*<<< orphan*/  pci_add_ext_cap_save_buffer (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int) ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 scalar_t__ pcie_aer_get_firmware_first (struct pci_dev*) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,struct dpc_dev*) ; 

__attribute__((used)) static int dpc_probe(struct pcie_device *dev)
{
	struct dpc_dev *dpc;
	struct pci_dev *pdev = dev->port;
	struct device *device = &dev->device;
	int status;
	u16 ctl, cap;

	if (pcie_aer_get_firmware_first(pdev))
		return -ENOTSUPP;

	dpc = devm_kzalloc(device, sizeof(*dpc), GFP_KERNEL);
	if (!dpc)
		return -ENOMEM;

	dpc->cap_pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_DPC);
	dpc->dev = dev;
	set_service_data(dev, dpc);

	status = devm_request_threaded_irq(device, dev->irq, dpc_irq,
					   dpc_handler, IRQF_SHARED,
					   "pcie-dpc", dpc);
	if (status) {
		pci_warn(pdev, "request IRQ%d failed: %d\n", dev->irq,
			 status);
		return status;
	}

	pci_read_config_word(pdev, dpc->cap_pos + PCI_EXP_DPC_CAP, &cap);
	pci_read_config_word(pdev, dpc->cap_pos + PCI_EXP_DPC_CTL, &ctl);

	dpc->rp_extensions = (cap & PCI_EXP_DPC_CAP_RP_EXT);
	if (dpc->rp_extensions) {
		dpc->rp_log_size = (cap & PCI_EXP_DPC_RP_PIO_LOG_SIZE) >> 8;
		if (dpc->rp_log_size < 4 || dpc->rp_log_size > 9) {
			pci_err(pdev, "RP PIO log size %u is invalid\n",
				dpc->rp_log_size);
			dpc->rp_log_size = 0;
		}
	}

	ctl = (ctl & 0xfff4) | PCI_EXP_DPC_CTL_EN_FATAL | PCI_EXP_DPC_CTL_INT_EN;
	pci_write_config_word(pdev, dpc->cap_pos + PCI_EXP_DPC_CTL, ctl);

	pci_info(pdev, "error containment capabilities: Int Msg #%d, RPExt%c PoisonedTLP%c SwTrigger%c RP PIO Log %d, DL_ActiveErr%c\n",
		 cap & PCI_EXP_DPC_IRQ, FLAG(cap, PCI_EXP_DPC_CAP_RP_EXT),
		 FLAG(cap, PCI_EXP_DPC_CAP_POISONED_TLP),
		 FLAG(cap, PCI_EXP_DPC_CAP_SW_TRIGGER), dpc->rp_log_size,
		 FLAG(cap, PCI_EXP_DPC_CAP_DL_ACTIVE));

	pci_add_ext_cap_save_buffer(pdev, PCI_EXT_CAP_ID_DPC, sizeof(u16));
	return status;
}