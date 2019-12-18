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
struct ifla_vf_info {int dummy; } ;
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* sriov_get_vf_config ) (struct efx_nic*,int,struct ifla_vf_info*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,int,struct ifla_vf_info*) ; 

int efx_sriov_get_vf_config(struct net_device *net_dev, int vf_i,
			    struct ifla_vf_info *ivi)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (efx->type->sriov_get_vf_config)
		return efx->type->sriov_get_vf_config(efx, vf_i, ivi);
	else
		return -EOPNOTSUPP;
}