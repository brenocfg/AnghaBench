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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mvpp2_port {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ MVPP2_PRS_VLAN_FILT_MAX ; 
 int mvpp2_prs_vid_entry_add (struct mvpp2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_vlan_rx_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int ret;

	ret = mvpp2_prs_vid_entry_add(port, vid);
	if (ret)
		netdev_err(dev, "rx-vlan-filter offloading cannot accept more than %d VIDs per port\n",
			   MVPP2_PRS_VLAN_FILT_MAX - 1);
	return ret;
}