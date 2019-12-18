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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ mbox_off; } ;
struct nfp_net {TYPE_1__ tlv_caps; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  NFP_NET_CFG_MBOX_CMD_CTAG_FILTER_KILL ; 
 scalar_t__ NFP_NET_CFG_VLAN_FILTER_PROTO ; 
 int /*<<< orphan*/  NFP_NET_CFG_VLAN_FILTER_SZ ; 
 scalar_t__ NFP_NET_CFG_VLAN_FILTER_VID ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int nfp_net_mbox_lock (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int nfp_net_mbox_reconfig_and_unlock (struct nfp_net*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  nn_writew (struct nfp_net*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_net_vlan_rx_kill_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_CTAG_FILTER_KILL;
	struct nfp_net *nn = netdev_priv(netdev);
	int err;

	/* Priority tagged packets with vlan id 0 are processed by the
	 * NFP as untagged packets
	 */
	if (!vid)
		return 0;

	err = nfp_net_mbox_lock(nn, NFP_NET_CFG_VLAN_FILTER_SZ);
	if (err)
		return err;

	nn_writew(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_VID, vid);
	nn_writew(nn, nn->tlv_caps.mbox_off + NFP_NET_CFG_VLAN_FILTER_PROTO,
		  ETH_P_8021Q);

	return nfp_net_mbox_reconfig_and_unlock(nn, cmd);
}