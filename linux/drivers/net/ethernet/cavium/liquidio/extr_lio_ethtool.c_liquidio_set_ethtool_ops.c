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
struct octeon_device {int dummy; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_ethtool_ops ; 
 int /*<<< orphan*/  lio_vf_ethtool_ops ; 

void liquidio_set_ethtool_ops(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;

	if (OCTEON_CN23XX_VF(oct))
		netdev->ethtool_ops = &lio_vf_ethtool_ops;
	else
		netdev->ethtool_ops = &lio_ethtool_ops;
}