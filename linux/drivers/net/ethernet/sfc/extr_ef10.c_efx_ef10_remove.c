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
struct efx_nic {TYPE_1__* pci_dev; int /*<<< orphan*/  net_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int vf_index; int /*<<< orphan*/  mcdi_buf; int /*<<< orphan*/  udp_tunnels_lock; int /*<<< orphan*/  udp_tunnels; int /*<<< orphan*/  must_restore_piobufs; scalar_t__ wc_membase; int /*<<< orphan*/  vlan_lock; struct ef10_vf* vf; } ;
struct ef10_vf {int /*<<< orphan*/ * efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct pci_dev* physfn; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_attr_link_control_flag ; 
 int /*<<< orphan*/  dev_attr_primary_flag ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ef10_cleanup_vlans (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ef10_free_piobufs (struct efx_nic*) ; 
 int efx_ef10_free_vis (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ef10_rx_free_indir_table (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ef10_set_udp_tnl_ports (struct efx_nic*,int) ; 
 int /*<<< orphan*/  efx_mcdi_detach (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_fini (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_mon_remove (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ptp_remove (struct efx_nic*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct efx_ef10_nic_data*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct efx_nic* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void efx_ef10_remove(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	int rc;

#ifdef CONFIG_SFC_SRIOV
	struct efx_ef10_nic_data *nic_data_pf;
	struct pci_dev *pci_dev_pf;
	struct efx_nic *efx_pf;
	struct ef10_vf *vf;

	if (efx->pci_dev->is_virtfn) {
		pci_dev_pf = efx->pci_dev->physfn;
		if (pci_dev_pf) {
			efx_pf = pci_get_drvdata(pci_dev_pf);
			nic_data_pf = efx_pf->nic_data;
			vf = nic_data_pf->vf + nic_data->vf_index;
			vf->efx = NULL;
		} else
			netif_info(efx, drv, efx->net_dev,
				   "Could not get the PF id from VF\n");
	}
#endif

	efx_ef10_cleanup_vlans(efx);
	mutex_destroy(&nic_data->vlan_lock);

	efx_ptp_remove(efx);

	efx_mcdi_mon_remove(efx);

	efx_ef10_rx_free_indir_table(efx);

	if (nic_data->wc_membase)
		iounmap(nic_data->wc_membase);

	rc = efx_ef10_free_vis(efx);
	WARN_ON(rc != 0);

	if (!nic_data->must_restore_piobufs)
		efx_ef10_free_piobufs(efx);

	device_remove_file(&efx->pci_dev->dev, &dev_attr_primary_flag);
	device_remove_file(&efx->pci_dev->dev, &dev_attr_link_control_flag);

	efx_mcdi_detach(efx);

	memset(nic_data->udp_tunnels, 0, sizeof(nic_data->udp_tunnels));
	mutex_lock(&nic_data->udp_tunnels_lock);
	(void)efx_ef10_set_udp_tnl_ports(efx, true);
	mutex_unlock(&nic_data->udp_tunnels_lock);

	mutex_destroy(&nic_data->udp_tunnels_lock);

	efx_mcdi_fini(efx);
	efx_nic_free_buffer(efx, &nic_data->mcdi_buf);
	kfree(nic_data);
}