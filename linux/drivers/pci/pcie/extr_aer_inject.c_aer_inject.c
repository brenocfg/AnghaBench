#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pcie_device {int /*<<< orphan*/  irq; struct pci_dev* port; } ;
struct pci_dev {int aer_cap; unsigned int devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct aer_error_inj {int bus; int cor_status; int uncor_status; int /*<<< orphan*/  header_log3; int /*<<< orphan*/  header_log2; int /*<<< orphan*/  header_log1; int /*<<< orphan*/  header_log0; int /*<<< orphan*/  domain; int /*<<< orphan*/  fn; int /*<<< orphan*/  dev; } ;
struct aer_error {int uncor_status; int cor_status; int root_status; int source_id; int /*<<< orphan*/  list; int /*<<< orphan*/  header_log3; int /*<<< orphan*/  header_log2; int /*<<< orphan*/  header_log1; int /*<<< orphan*/  header_log0; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIE_PORT_SERVICE_AER ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 int PCI_ERR_ROOT_COR_RCV ; 
 int PCI_ERR_ROOT_FATAL_RCV ; 
 int PCI_ERR_ROOT_FIRST_FATAL ; 
 int PCI_ERR_ROOT_MULTI_COR_RCV ; 
 int PCI_ERR_ROOT_MULTI_UNCOR_RCV ; 
 int PCI_ERR_ROOT_NONFATAL_RCV ; 
 int PCI_ERR_ROOT_UNCOR_RCV ; 
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_SEVER ; 
 struct aer_error* __find_aer_error_by_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  aer_error_init (struct aer_error*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 scalar_t__ aer_mask_override ; 
 int /*<<< orphan*/  einjected ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  inject_lock ; 
 int /*<<< orphan*/  kfree (struct aer_error*) ; 
 struct aer_error* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int pci_bus_set_aer_ops (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 struct pci_dev* pcie_find_root_port (struct pci_dev*) ; 
 struct device* pcie_port_find_device (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pcie_device* to_pcie_device (struct device*) ; 

__attribute__((used)) static int aer_inject(struct aer_error_inj *einj)
{
	struct aer_error *err, *rperr;
	struct aer_error *err_alloc = NULL, *rperr_alloc = NULL;
	struct pci_dev *dev, *rpdev;
	struct pcie_device *edev;
	struct device *device;
	unsigned long flags;
	unsigned int devfn = PCI_DEVFN(einj->dev, einj->fn);
	int pos_cap_err, rp_pos_cap_err;
	u32 sever, cor_mask, uncor_mask, cor_mask_orig = 0, uncor_mask_orig = 0;
	int ret = 0;

	dev = pci_get_domain_bus_and_slot(einj->domain, einj->bus, devfn);
	if (!dev)
		return -ENODEV;
	rpdev = pcie_find_root_port(dev);
	if (!rpdev) {
		pci_err(dev, "Root port not found\n");
		ret = -ENODEV;
		goto out_put;
	}

	pos_cap_err = dev->aer_cap;
	if (!pos_cap_err) {
		pci_err(dev, "Device doesn't support AER\n");
		ret = -EPROTONOSUPPORT;
		goto out_put;
	}
	pci_read_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_SEVER, &sever);
	pci_read_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK, &cor_mask);
	pci_read_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
			      &uncor_mask);

	rp_pos_cap_err = rpdev->aer_cap;
	if (!rp_pos_cap_err) {
		pci_err(rpdev, "Root port doesn't support AER\n");
		ret = -EPROTONOSUPPORT;
		goto out_put;
	}

	err_alloc =  kzalloc(sizeof(struct aer_error), GFP_KERNEL);
	if (!err_alloc) {
		ret = -ENOMEM;
		goto out_put;
	}
	rperr_alloc =  kzalloc(sizeof(struct aer_error), GFP_KERNEL);
	if (!rperr_alloc) {
		ret = -ENOMEM;
		goto out_put;
	}

	if (aer_mask_override) {
		cor_mask_orig = cor_mask;
		cor_mask &= !(einj->cor_status);
		pci_write_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK,
				       cor_mask);

		uncor_mask_orig = uncor_mask;
		uncor_mask &= !(einj->uncor_status);
		pci_write_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
				       uncor_mask);
	}

	spin_lock_irqsave(&inject_lock, flags);

	err = __find_aer_error_by_dev(dev);
	if (!err) {
		err = err_alloc;
		err_alloc = NULL;
		aer_error_init(err, einj->domain, einj->bus, devfn,
			       pos_cap_err);
		list_add(&err->list, &einjected);
	}
	err->uncor_status |= einj->uncor_status;
	err->cor_status |= einj->cor_status;
	err->header_log0 = einj->header_log0;
	err->header_log1 = einj->header_log1;
	err->header_log2 = einj->header_log2;
	err->header_log3 = einj->header_log3;

	if (!aer_mask_override && einj->cor_status &&
	    !(einj->cor_status & ~cor_mask)) {
		ret = -EINVAL;
		pci_warn(dev, "The correctable error(s) is masked by device\n");
		spin_unlock_irqrestore(&inject_lock, flags);
		goto out_put;
	}
	if (!aer_mask_override && einj->uncor_status &&
	    !(einj->uncor_status & ~uncor_mask)) {
		ret = -EINVAL;
		pci_warn(dev, "The uncorrectable error(s) is masked by device\n");
		spin_unlock_irqrestore(&inject_lock, flags);
		goto out_put;
	}

	rperr = __find_aer_error_by_dev(rpdev);
	if (!rperr) {
		rperr = rperr_alloc;
		rperr_alloc = NULL;
		aer_error_init(rperr, pci_domain_nr(rpdev->bus),
			       rpdev->bus->number, rpdev->devfn,
			       rp_pos_cap_err);
		list_add(&rperr->list, &einjected);
	}
	if (einj->cor_status) {
		if (rperr->root_status & PCI_ERR_ROOT_COR_RCV)
			rperr->root_status |= PCI_ERR_ROOT_MULTI_COR_RCV;
		else
			rperr->root_status |= PCI_ERR_ROOT_COR_RCV;
		rperr->source_id &= 0xffff0000;
		rperr->source_id |= (einj->bus << 8) | devfn;
	}
	if (einj->uncor_status) {
		if (rperr->root_status & PCI_ERR_ROOT_UNCOR_RCV)
			rperr->root_status |= PCI_ERR_ROOT_MULTI_UNCOR_RCV;
		if (sever & einj->uncor_status) {
			rperr->root_status |= PCI_ERR_ROOT_FATAL_RCV;
			if (!(rperr->root_status & PCI_ERR_ROOT_UNCOR_RCV))
				rperr->root_status |= PCI_ERR_ROOT_FIRST_FATAL;
		} else
			rperr->root_status |= PCI_ERR_ROOT_NONFATAL_RCV;
		rperr->root_status |= PCI_ERR_ROOT_UNCOR_RCV;
		rperr->source_id &= 0x0000ffff;
		rperr->source_id |= ((einj->bus << 8) | devfn) << 16;
	}
	spin_unlock_irqrestore(&inject_lock, flags);

	if (aer_mask_override) {
		pci_write_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK,
				       cor_mask_orig);
		pci_write_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
				       uncor_mask_orig);
	}

	ret = pci_bus_set_aer_ops(dev->bus);
	if (ret)
		goto out_put;
	ret = pci_bus_set_aer_ops(rpdev->bus);
	if (ret)
		goto out_put;

	device = pcie_port_find_device(rpdev, PCIE_PORT_SERVICE_AER);
	if (device) {
		edev = to_pcie_device(device);
		if (!get_service_data(edev)) {
			pci_warn(edev->port, "AER service is not initialized\n");
			ret = -EPROTONOSUPPORT;
			goto out_put;
		}
		pci_info(edev->port, "Injecting errors %08x/%08x into device %s\n",
			 einj->cor_status, einj->uncor_status, pci_name(dev));
		local_irq_disable();
		generic_handle_irq(edev->irq);
		local_irq_enable();
	} else {
		pci_err(rpdev, "AER device not found\n");
		ret = -ENODEV;
	}
out_put:
	kfree(err_alloc);
	kfree(rperr_alloc);
	pci_dev_put(dev);
	return ret;
}