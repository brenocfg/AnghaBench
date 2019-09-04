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
typedef  int u16 ;
struct nfp_tun_mac_offload_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; int /*<<< orphan*/  index; } ;
struct nfp_flower_priv {int /*<<< orphan*/  nfp_mac_off_lock; int /*<<< orphan*/  nfp_mac_off_list; int /*<<< orphan*/  nfp_mac_off_count; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_TYPE ; 
 int NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT ; 
 int NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT ; 
 int NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_tun_mac_offload_entry*) ; 
 struct nfp_tun_mac_offload_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int nfp_repr_get_port_id (struct net_device*) ; 
 int nfp_tun_get_mac_idx (struct nfp_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_tun_is_netdev_to_offload (struct net_device*) ; 

__attribute__((used)) static void nfp_tun_add_to_mac_offload_list(struct net_device *netdev,
					    struct nfp_app *app)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_tun_mac_offload_entry *entry;
	u16 nfp_mac_idx;
	int port = 0;

	/* Check if MAC should be offloaded. */
	if (!is_valid_ether_addr(netdev->dev_addr))
		return;

	if (nfp_netdev_is_nfp_repr(netdev))
		port = nfp_repr_get_port_id(netdev);
	else if (!nfp_tun_is_netdev_to_offload(netdev))
		return;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		nfp_flower_cmsg_warn(app, "Mem fail when offloading MAC.\n");
		return;
	}

	if (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port) ==
	    NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT) {
		nfp_mac_idx = port << 8 | NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT;
	} else if (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port) ==
		   NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT) {
		port = FIELD_GET(NFP_FLOWER_CMSG_PORT_VNIC, port);
		nfp_mac_idx = port << 8 | NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT;
	} else {
		/* Must assign our own unique 8-bit index. */
		int idx = nfp_tun_get_mac_idx(app, netdev->ifindex);

		if (idx < 0) {
			nfp_flower_cmsg_warn(app, "Can't assign non-repr MAC index.\n");
			kfree(entry);
			return;
		}
		nfp_mac_idx = idx << 8 | NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT;
	}

	entry->index = cpu_to_be16(nfp_mac_idx);
	ether_addr_copy(entry->addr, netdev->dev_addr);

	mutex_lock(&priv->nfp_mac_off_lock);
	priv->nfp_mac_off_count++;
	list_add_tail(&entry->list, &priv->nfp_mac_off_list);
	mutex_unlock(&priv->nfp_mac_off_lock);
}