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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_dev_data {int dummy; } ;
struct amd_ntb_dev {int /*<<< orphan*/  ntb; struct ntb_dev_data* dev_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amd_deinit_dev (struct amd_ntb_dev*) ; 
 int amd_init_dev (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  amd_init_side_info (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  amd_ntb_deinit_pci (struct amd_ntb_dev*) ; 
 int amd_ntb_init_pci (struct amd_ntb_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  amd_poll_link (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amd_ntb_dev*) ; 
 struct amd_ntb_dev* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndev_deinit_debugfs (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  ndev_init_debugfs (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  ndev_init_struct (struct amd_ntb_dev*,struct pci_dev*) ; 
 int ntb_register_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd_ntb_pci_probe(struct pci_dev *pdev,
			     const struct pci_device_id *id)
{
	struct amd_ntb_dev *ndev;
	int rc, node;

	node = dev_to_node(&pdev->dev);

	ndev = kzalloc_node(sizeof(*ndev), GFP_KERNEL, node);
	if (!ndev) {
		rc = -ENOMEM;
		goto err_ndev;
	}

	ndev->dev_data = (struct ntb_dev_data *)id->driver_data;

	ndev_init_struct(ndev, pdev);

	rc = amd_ntb_init_pci(ndev, pdev);
	if (rc)
		goto err_init_pci;

	rc = amd_init_dev(ndev);
	if (rc)
		goto err_init_dev;

	/* write side info */
	amd_init_side_info(ndev);

	amd_poll_link(ndev);

	ndev_init_debugfs(ndev);

	rc = ntb_register_device(&ndev->ntb);
	if (rc)
		goto err_register;

	dev_info(&pdev->dev, "NTB device registered.\n");

	return 0;

err_register:
	ndev_deinit_debugfs(ndev);
	amd_deinit_dev(ndev);
err_init_dev:
	amd_ntb_deinit_pci(ndev);
err_init_pci:
	kfree(ndev);
err_ndev:
	return rc;
}