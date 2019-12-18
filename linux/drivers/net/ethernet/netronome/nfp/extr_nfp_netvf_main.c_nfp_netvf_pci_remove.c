#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct nfp_net_vf {int /*<<< orphan*/  q_bar; int /*<<< orphan*/  ddir; struct nfp_net* nn; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_bar; } ;
struct nfp_net {TYPE_1__ dp; int /*<<< orphan*/  tx_bar; int /*<<< orphan*/  rx_bar; int /*<<< orphan*/  debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_net_vf*) ; 
 int /*<<< orphan*/  nfp_net_clean (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_debugfs_dir_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_free (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_irqs_disable (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct nfp_net_vf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_netvf_pci_remove(struct pci_dev *pdev)
{
	struct nfp_net_vf *vf;
	struct nfp_net *nn;

	vf = pci_get_drvdata(pdev);
	if (!vf)
		return;

	nn = vf->nn;

	/* Note, the order is slightly different from above as we need
	 * to keep the nn pointer around till we have freed everything.
	 */
	nfp_net_debugfs_dir_clean(&nn->debugfs_dir);
	nfp_net_debugfs_dir_clean(&vf->ddir);

	nfp_net_clean(nn);

	nfp_net_irqs_disable(pdev);

	if (!vf->q_bar) {
		iounmap(nn->rx_bar);
		iounmap(nn->tx_bar);
	} else {
		iounmap(vf->q_bar);
	}
	iounmap(nn->dp.ctrl_bar);

	nfp_net_free(nn);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	pci_set_drvdata(pdev, NULL);
	kfree(vf);
}