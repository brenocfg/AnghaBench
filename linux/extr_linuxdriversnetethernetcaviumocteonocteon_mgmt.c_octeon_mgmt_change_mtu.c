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
struct octeon_mgmt {scalar_t__ agl; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 scalar_t__ AGL_GMX_RX_FRM_MAX ; 
 scalar_t__ AGL_GMX_RX_JABBER ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int octeon_mgmt_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	int max_packet = new_mtu + ETH_HLEN + ETH_FCS_LEN;

	netdev->mtu = new_mtu;

	/* HW lifts the limit if the frame is VLAN tagged
	 * (+4 bytes per each tag, up to two tags)
	 */
	cvmx_write_csr(p->agl + AGL_GMX_RX_FRM_MAX, max_packet);
	/* Set the hardware to truncate packets larger than the MTU. The jabber
	 * register must be set to a multiple of 8 bytes, so round up. JABBER is
	 * an unconditional limit, so we need to account for two possible VLAN
	 * tags.
	 */
	cvmx_write_csr(p->agl + AGL_GMX_RX_JABBER,
		       (max_packet + 7 + VLAN_HLEN * 2) & 0xfff8);

	return 0;
}