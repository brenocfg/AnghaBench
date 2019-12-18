#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct cxl {int tunneled_ops_supported; TYPE_3__* native; TYPE_1__ dev; } ;
struct TYPE_6__ {TYPE_2__* sl_ops; } ;
struct TYPE_5__ {int (* adapter_regs_init ) (struct cxl*,struct pci_dev*) ;int /*<<< orphan*/  capi_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PHB_CAPI_MODE_SNOOP_ON ; 
 int /*<<< orphan*/  cxl_fixup_malformed_tlp (struct cxl*,struct pci_dev*) ; 
 scalar_t__ cxl_is_power9 () ; 
 int cxl_map_adapter_regs (struct cxl*,struct pci_dev*) ; 
 int cxl_native_register_psl_err_irq (struct cxl*) ; 
 int cxl_read_vsec (struct cxl*,struct pci_dev*) ; 
 int /*<<< orphan*/  cxl_release_adapter ; 
 int /*<<< orphan*/  cxl_setup_psl_timebase (struct cxl*,struct pci_dev*) ; 
 int /*<<< orphan*/  cxl_unmap_adapter_regs (struct cxl*) ; 
 int cxl_update_image_control (struct cxl*) ; 
 int cxl_vsec_looks_ok (struct cxl*,struct pci_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cxl*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ pnv_pci_set_tunnel_bar (struct pci_dev*,int,int) ; 
 int pnv_phb_to_cxl_mode (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int sanitise_adapter_regs (struct cxl*) ; 
 int setup_cxl_bars (struct pci_dev*) ; 
 int stub1 (struct cxl*,struct pci_dev*) ; 
 int switch_card_to_cxl (struct pci_dev*) ; 

__attribute__((used)) static int cxl_configure_adapter(struct cxl *adapter, struct pci_dev *dev)
{
	int rc;

	adapter->dev.parent = &dev->dev;
	adapter->dev.release = cxl_release_adapter;
	pci_set_drvdata(dev, adapter);

	rc = pci_enable_device(dev);
	if (rc) {
		dev_err(&dev->dev, "pci_enable_device failed: %i\n", rc);
		return rc;
	}

	if ((rc = cxl_read_vsec(adapter, dev)))
		return rc;

	if ((rc = cxl_vsec_looks_ok(adapter, dev)))
	        return rc;

	cxl_fixup_malformed_tlp(adapter, dev);

	if ((rc = setup_cxl_bars(dev)))
		return rc;

	if ((rc = switch_card_to_cxl(dev)))
		return rc;

	if ((rc = cxl_update_image_control(adapter)))
		return rc;

	if ((rc = cxl_map_adapter_regs(adapter, dev)))
		return rc;

	if ((rc = sanitise_adapter_regs(adapter)))
		goto err;

	if ((rc = adapter->native->sl_ops->adapter_regs_init(adapter, dev)))
		goto err;

	/* Required for devices using CAPP DMA mode, harmless for others */
	pci_set_master(dev);

	adapter->tunneled_ops_supported = false;

	if (cxl_is_power9()) {
		if (pnv_pci_set_tunnel_bar(dev, 0x00020000E0000000ull, 1))
			dev_info(&dev->dev, "Tunneled operations unsupported\n");
		else
			adapter->tunneled_ops_supported = true;
	}

	if ((rc = pnv_phb_to_cxl_mode(dev, adapter->native->sl_ops->capi_mode)))
		goto err;

	/* If recovery happened, the last step is to turn on snooping.
	 * In the non-recovery case this has no effect */
	if ((rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_ON)))
		goto err;

	/* Ignore error, adapter init is not dependant on timebase sync */
	cxl_setup_psl_timebase(adapter, dev);

	if ((rc = cxl_native_register_psl_err_irq(adapter)))
		goto err;

	return 0;

err:
	cxl_unmap_adapter_regs(adapter);
	return rc;

}