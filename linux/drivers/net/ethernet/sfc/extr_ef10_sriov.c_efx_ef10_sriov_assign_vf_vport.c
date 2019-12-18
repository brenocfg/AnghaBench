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
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {struct ef10_vf* vf; } ;
struct ef10_vf {int vport_assigned; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVB_PORT_ID_ASSIGNED ; 
 int /*<<< orphan*/  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int efx_ef10_evb_port_assign (struct efx_nic*,int /*<<< orphan*/ ,unsigned int) ; 
 int efx_ef10_vport_add_mac (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_ef10_vport_alloc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_sriov_assign_vf_vport(struct efx_nic *efx,
					  unsigned int vf_i)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	struct ef10_vf *vf = nic_data->vf + vf_i;
	int rc;

	if (WARN_ON_ONCE(!nic_data->vf))
		return -EOPNOTSUPP;

	rc = efx_ef10_vport_alloc(efx, EVB_PORT_ID_ASSIGNED,
				  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL,
				  vf->vlan, &vf->vport_id);
	if (rc)
		return rc;

	rc = efx_ef10_vport_add_mac(efx, vf->vport_id, vf->mac);
	if (rc) {
		eth_zero_addr(vf->mac);
		return rc;
	}

	rc =  efx_ef10_evb_port_assign(efx, vf->vport_id, vf_i);
	if (rc)
		return rc;

	vf->vport_assigned = 1;
	return 0;
}