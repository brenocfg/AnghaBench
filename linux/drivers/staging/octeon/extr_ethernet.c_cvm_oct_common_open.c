#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int en; int /*<<< orphan*/  pknd; } ;
union cvmx_gmxx_prtx_cfg {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct octeon_ethernet {void (* poll ) (struct net_device*) ;int /*<<< orphan*/  port; } ;
struct net_device {TYPE_4__* phydev; } ;
struct TYPE_7__ {int /*<<< orphan*/  link_up; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;
struct TYPE_9__ {scalar_t__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int /*<<< orphan*/  cvm_oct_adjust_link (struct net_device*) ; 
 int cvm_oct_phy_setup_device (struct net_device*) ; 
 TYPE_3__ cvmx_helper_link_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_is_simulation () ; 
 int phy_read_status (TYPE_4__*) ; 

int cvm_oct_common_open(struct net_device *dev,
			void (*link_poll)(struct net_device *))
{
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);
	cvmx_helper_link_info_t link_info;
	int rv;

	rv = cvm_oct_phy_setup_device(dev);
	if (rv)
		return rv;

	gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	gmx_cfg.s.en = 1;
	if (octeon_has_feature(OCTEON_FEATURE_PKND))
		gmx_cfg.s.pknd = priv->port;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);

	if (octeon_is_simulation())
		return 0;

	if (dev->phydev) {
		int r = phy_read_status(dev->phydev);

		if (r == 0 && dev->phydev->link == 0)
			netif_carrier_off(dev);
		cvm_oct_adjust_link(dev);
	} else {
		link_info = cvmx_helper_link_get(priv->port);
		if (!link_info.s.link_up)
			netif_carrier_off(dev);
		priv->poll = link_poll;
		link_poll(dev);
	}

	return 0;
}