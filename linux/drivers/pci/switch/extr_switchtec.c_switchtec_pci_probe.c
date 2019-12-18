#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  devt; } ;
struct switchtec_dev {TYPE_2__ dev; int /*<<< orphan*/  cdev; scalar_t__ dma_mrpc; TYPE_1__* mmio_part_cfg; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int class; } ;
struct TYPE_6__ {int /*<<< orphan*/  mrpc_comp_hdr; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct switchtec_dev*) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PCI_CLASS_BRIDGE_OTHER ; 
 int PTR_ERR (struct switchtec_dev*) ; 
 int SWITCHTEC_EVENT_CLEAR ; 
 int SWITCHTEC_EVENT_EN_IRQ ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  enable_dma_mrpc (struct switchtec_dev*) ; 
 int /*<<< orphan*/  enable_link_state_events (struct switchtec_dev*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  request_module_nowait (char*) ; 
 struct switchtec_dev* stdev_create (struct pci_dev*) ; 
 int /*<<< orphan*/  stdev_kill (struct switchtec_dev*) ; 
 int switchtec_init_isr (struct switchtec_dev*) ; 
 int switchtec_init_pci (struct switchtec_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  switchtec_minor_ida ; 

__attribute__((used)) static int switchtec_pci_probe(struct pci_dev *pdev,
			       const struct pci_device_id *id)
{
	struct switchtec_dev *stdev;
	int rc;

	if (pdev->class == (PCI_CLASS_BRIDGE_OTHER << 8))
		request_module_nowait("ntb_hw_switchtec");

	stdev = stdev_create(pdev);
	if (IS_ERR(stdev))
		return PTR_ERR(stdev);

	rc = switchtec_init_pci(stdev, pdev);
	if (rc)
		goto err_put;

	rc = switchtec_init_isr(stdev);
	if (rc) {
		dev_err(&stdev->dev, "failed to init isr.\n");
		goto err_put;
	}

	iowrite32(SWITCHTEC_EVENT_CLEAR |
		  SWITCHTEC_EVENT_EN_IRQ,
		  &stdev->mmio_part_cfg->mrpc_comp_hdr);
	enable_link_state_events(stdev);

	if (stdev->dma_mrpc)
		enable_dma_mrpc(stdev);

	rc = cdev_device_add(&stdev->cdev, &stdev->dev);
	if (rc)
		goto err_devadd;

	dev_info(&stdev->dev, "Management device registered.\n");

	return 0;

err_devadd:
	stdev_kill(stdev);
err_put:
	ida_simple_remove(&switchtec_minor_ida, MINOR(stdev->dev.devt));
	put_device(&stdev->dev);
	return rc;
}