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
struct net_device {int dummy; } ;
struct ifla_vf_info {int vf; scalar_t__ qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  mac; scalar_t__ min_tx_rate; int /*<<< orphan*/  max_tx_rate; } ;
struct fm10k_vf_info {int /*<<< orphan*/  pf_vid; int /*<<< orphan*/  mac; int /*<<< orphan*/  rate; } ;
struct fm10k_iov_data {int num_vfs; struct fm10k_vf_info* vf_info; } ;
struct fm10k_intfc {struct fm10k_iov_data* iov_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

int fm10k_ndo_get_vf_config(struct net_device *netdev,
			    int vf_idx, struct ifla_vf_info *ivi)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_iov_data *iov_data = interface->iov_data;
	struct fm10k_vf_info *vf_info;

	/* verify SR-IOV is active and that vf idx is valid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		return -EINVAL;

	vf_info = &iov_data->vf_info[vf_idx];

	ivi->vf = vf_idx;
	ivi->max_tx_rate = vf_info->rate;
	ivi->min_tx_rate = 0;
	ether_addr_copy(ivi->mac, vf_info->mac);
	ivi->vlan = vf_info->pf_vid;
	ivi->qos = 0;

	return 0;
}