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
struct pci_dev {int dummy; } ;
struct enetc_si {int /*<<< orphan*/  ndev; } ;
struct enetc_ndev_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  enetc_drv_name ; 
 int /*<<< orphan*/  enetc_drv_ver ; 
 int /*<<< orphan*/  enetc_free_msix (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_free_si_resources (struct enetc_ndev_priv*) ; 
 int /*<<< orphan*/  enetc_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 struct enetc_ndev_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct enetc_ndev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enetc_si* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_vf_remove(struct pci_dev *pdev)
{
	struct enetc_si *si = pci_get_drvdata(pdev);
	struct enetc_ndev_priv *priv;

	priv = netdev_priv(si->ndev);
	netif_info(priv, drv, si->ndev, "%s v%s remove\n",
		   enetc_drv_name, enetc_drv_ver);
	unregister_netdev(si->ndev);

	enetc_free_msix(priv);

	enetc_free_si_resources(priv);

	free_netdev(si->ndev);

	enetc_pci_remove(pdev);
}