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
struct net_device {int features; } ;
struct mvpp2_port {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  mvpp22_port_rss_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_port_rss_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_prs_vid_disable_filtering (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_prs_vid_enable_filtering (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_prs_vid_remove_all (struct mvpp2_port*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_set_features(struct net_device *dev,
			      netdev_features_t features)
{
	netdev_features_t changed = dev->features ^ features;
	struct mvpp2_port *port = netdev_priv(dev);

	if (changed & NETIF_F_HW_VLAN_CTAG_FILTER) {
		if (features & NETIF_F_HW_VLAN_CTAG_FILTER) {
			mvpp2_prs_vid_enable_filtering(port);
		} else {
			/* Invalidate all registered VID filters for this
			 * port
			 */
			mvpp2_prs_vid_remove_all(port);

			mvpp2_prs_vid_disable_filtering(port);
		}
	}

	if (changed & NETIF_F_RXHASH) {
		if (features & NETIF_F_RXHASH)
			mvpp22_port_rss_enable(port);
		else
			mvpp22_port_rss_disable(port);
	}

	return 0;
}