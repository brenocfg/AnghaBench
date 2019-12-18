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
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_2__ {scalar_t__ pf_id; } ;
struct i40e_pf {TYPE_1__ hw; int /*<<< orphan*/  pdev; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_priv_flags; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 scalar_t__ I40E_GL_PRIV_FLAGS_STR_LEN ; 
 int /*<<< orphan*/  I40E_PRIV_FLAGS_STR_LEN ; 
 int /*<<< orphan*/  i40e_driver_name ; 
 int /*<<< orphan*/  i40e_driver_version_str ; 
 int /*<<< orphan*/  i40e_nvm_version_str (TYPE_1__*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_get_drvinfo(struct net_device *netdev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;

	strlcpy(drvinfo->driver, i40e_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, i40e_driver_version_str,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->fw_version, i40e_nvm_version_str(&pf->hw),
		sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(pf->pdev),
		sizeof(drvinfo->bus_info));
	drvinfo->n_priv_flags = I40E_PRIV_FLAGS_STR_LEN;
	if (pf->hw.pf_id == 0)
		drvinfo->n_priv_flags += I40E_GL_PRIV_FLAGS_STR_LEN;
}