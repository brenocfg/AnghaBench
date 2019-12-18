#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {scalar_t__ link_info; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ link_up; } ;
struct TYPE_7__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvm_oct_check_preamble_errors (struct net_device*) ; 
 int /*<<< orphan*/  cvm_oct_note_carrier (struct octeon_ethernet*,TYPE_2__) ; 
 TYPE_2__ cvmx_helper_link_get (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_helper_link_set (int /*<<< orphan*/ ,TYPE_2__) ; 
 scalar_t__ likely (int) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static void cvm_oct_rgmii_poll(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;
	bool status_change;

	link_info = cvmx_helper_link_get(priv->port);
	if (priv->link_info != link_info.u64 &&
	    cvmx_helper_link_set(priv->port, link_info))
		link_info.u64 = priv->link_info;
	status_change = priv->link_info != link_info.u64;
	priv->link_info = link_info.u64;

	cvm_oct_check_preamble_errors(dev);

	if (likely(!status_change))
		return;

	/* Tell core. */
	if (link_info.s.link_up) {
		if (!netif_carrier_ok(dev))
			netif_carrier_on(dev);
	} else if (netif_carrier_ok(dev)) {
		netif_carrier_off(dev);
	}
	cvm_oct_note_carrier(priv, link_info);
}