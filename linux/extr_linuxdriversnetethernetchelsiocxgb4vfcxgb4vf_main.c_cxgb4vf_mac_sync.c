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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct port_info {int /*<<< orphan*/  viid; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct hash_mac_addr {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; } ;
struct adapter {int /*<<< orphan*/  mac_hlist; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int cxgb4vf_set_addr_hash (struct port_info*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int is_unicast_ether_addr (int /*<<< orphan*/  const*) ; 
 struct hash_mac_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4vf_alloc_mac_filt (struct adapter*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static int cxgb4vf_mac_sync(struct net_device *netdev, const u8 *mac_addr)
{
	struct port_info *pi = netdev_priv(netdev);
	struct adapter *adapter = pi->adapter;
	int ret;
	u64 mhash = 0;
	u64 uhash = 0;
	bool free = false;
	bool ucast = is_unicast_ether_addr(mac_addr);
	const u8 *maclist[1] = {mac_addr};
	struct hash_mac_addr *new_entry;

	ret = t4vf_alloc_mac_filt(adapter, pi->viid, free, 1, maclist,
				  NULL, ucast ? &uhash : &mhash, false);
	if (ret < 0)
		goto out;
	/* if hash != 0, then add the addr to hash addr list
	 * so on the end we will calculate the hash for the
	 * list and program it
	 */
	if (uhash || mhash) {
		new_entry = kzalloc(sizeof(*new_entry), GFP_ATOMIC);
		if (!new_entry)
			return -ENOMEM;
		ether_addr_copy(new_entry->addr, mac_addr);
		list_add_tail(&new_entry->list, &adapter->mac_hlist);
		ret = cxgb4vf_set_addr_hash(pi);
	}
out:
	return ret < 0 ? ret : 0;
}