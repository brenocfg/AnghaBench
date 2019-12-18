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
struct wd719x {int /*<<< orphan*/  base; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 struct wd719x* shost_priv (struct Scsi_Host*) ; 
 int wd719x_board_found (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wd719x_destroy (struct wd719x*) ; 
 int /*<<< orphan*/  wd719x_template ; 

__attribute__((used)) static int wd719x_pci_probe(struct pci_dev *pdev, const struct pci_device_id *d)
{
	int err;
	struct Scsi_Host *sh;
	struct wd719x *wd;

	err = pci_enable_device(pdev);
	if (err)
		goto fail;

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_warn(&pdev->dev, "Unable to set 32-bit DMA mask\n");
		goto disable_device;
	}

	err = pci_request_regions(pdev, "wd719x");
	if (err)
		goto disable_device;
	pci_set_master(pdev);

	err = -ENODEV;
	if (pci_resource_len(pdev, 0) == 0)
		goto release_region;

	err = -ENOMEM;
	sh = scsi_host_alloc(&wd719x_template, sizeof(struct wd719x));
	if (!sh)
		goto release_region;

	wd = shost_priv(sh);
	wd->base = pci_iomap(pdev, 0, 0);
	if (!wd->base)
		goto free_host;
	wd->pdev = pdev;

	err = wd719x_board_found(sh);
	if (err)
		goto unmap;

	err = scsi_add_host(sh, &wd->pdev->dev);
	if (err)
		goto destroy;

	scsi_scan_host(sh);

	pci_set_drvdata(pdev, sh);
	return 0;

destroy:
	wd719x_destroy(wd);
unmap:
	pci_iounmap(pdev, wd->base);
free_host:
	scsi_host_put(sh);
release_region:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);
fail:
	return err;
}