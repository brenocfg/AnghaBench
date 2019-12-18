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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct nfp_cpp {int dummy; } ;
struct nfp6000_pcie {int /*<<< orphan*/  bar_lock; int /*<<< orphan*/  bar_waiters; struct pci_dev* pdev; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct nfp_cpp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFP_CPP_INTERFACE_CHANNEL_PEROPENER ; 
 scalar_t__ NFP_CPP_INTERFACE_CHANNEL_of (int /*<<< orphan*/ ) ; 
 scalar_t__ NFP_CPP_INTERFACE_TYPE_PCI ; 
 scalar_t__ NFP_CPP_INTERFACE_TYPE_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int enable_bars (struct nfp6000_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfp6000_pcie*) ; 
 struct nfp6000_pcie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp6000_get_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp6000_pcie_ops ; 
 struct nfp_cpp* nfp_cpp_from_operations (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nfp6000_pcie*) ; 
 int /*<<< orphan*/  pcie_print_link_status (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct nfp_cpp *nfp_cpp_from_nfp6000_pcie(struct pci_dev *pdev)
{
	struct nfp6000_pcie *nfp;
	u16 interface;
	int err;

	/*  Finished with card initialization. */
	dev_info(&pdev->dev,
		 "Netronome Flow Processor NFP4000/NFP5000/NFP6000 PCIe Card Probe\n");
	pcie_print_link_status(pdev);

	nfp = kzalloc(sizeof(*nfp), GFP_KERNEL);
	if (!nfp) {
		err = -ENOMEM;
		goto err_ret;
	}

	nfp->dev = &pdev->dev;
	nfp->pdev = pdev;
	init_waitqueue_head(&nfp->bar_waiters);
	spin_lock_init(&nfp->bar_lock);

	interface = nfp6000_get_interface(&pdev->dev);

	if (NFP_CPP_INTERFACE_TYPE_of(interface) !=
	    NFP_CPP_INTERFACE_TYPE_PCI) {
		dev_err(&pdev->dev,
			"Interface type %d is not the expected %d\n",
			NFP_CPP_INTERFACE_TYPE_of(interface),
			NFP_CPP_INTERFACE_TYPE_PCI);
		err = -ENODEV;
		goto err_free_nfp;
	}

	if (NFP_CPP_INTERFACE_CHANNEL_of(interface) !=
	    NFP_CPP_INTERFACE_CHANNEL_PEROPENER) {
		dev_err(&pdev->dev, "Interface channel %d is not the expected %d\n",
			NFP_CPP_INTERFACE_CHANNEL_of(interface),
			NFP_CPP_INTERFACE_CHANNEL_PEROPENER);
		err = -ENODEV;
		goto err_free_nfp;
	}

	err = enable_bars(nfp, interface);
	if (err)
		goto err_free_nfp;

	/* Probe for all the common NFP devices */
	return nfp_cpp_from_operations(&nfp6000_pcie_ops, &pdev->dev, nfp);

err_free_nfp:
	kfree(nfp);
err_ret:
	dev_err(&pdev->dev, "NFP6000 PCI setup failed\n");
	return ERR_PTR(err);
}