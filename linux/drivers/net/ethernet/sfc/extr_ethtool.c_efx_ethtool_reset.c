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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* map_reset_flags ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int efx_reset (struct efx_nic*,int) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ethtool_reset(struct net_device *net_dev, u32 *flags)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	int rc;

	rc = efx->type->map_reset_flags(flags);
	if (rc < 0)
		return rc;

	return efx_reset(efx, rc);
}