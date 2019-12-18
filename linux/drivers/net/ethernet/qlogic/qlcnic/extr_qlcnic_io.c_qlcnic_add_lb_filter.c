#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qlcnic_filter {unsigned long ftime; int vlan_id; int /*<<< orphan*/  fnode; scalar_t__* faddr; } ;
struct TYPE_4__ {scalar_t__ fnum; scalar_t__ fmax; struct hlist_head* fhead; } ;
struct TYPE_3__ {int fbucket_size; int /*<<< orphan*/  fnum; struct hlist_head* fhead; } ;
struct qlcnic_adapter {int /*<<< orphan*/  rx_mac_learn_lock; TYPE_2__ rx_fhash; int /*<<< orphan*/  mac_learn_lock; TYPE_1__ fhash; } ;
struct hlist_head {int dummy; } ;
struct ethhdr {scalar_t__* h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long HZ ; 
 size_t QLCNIC_MAC_DEL ; 
 size_t QLCNIC_MAC_VLAN_DEL ; 
 unsigned long QLCNIC_READD_AGE ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 struct qlcnic_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_delete_rx_list_mac (struct qlcnic_adapter*,struct qlcnic_filter*,scalar_t__*,int) ; 
 struct qlcnic_filter* qlcnic_find_mac_filter (struct hlist_head*,scalar_t__*,int) ; 
 int qlcnic_mac_hash (scalar_t__,int) ; 
 int qlcnic_sre_macaddr_change (struct qlcnic_adapter*,size_t*,int,size_t) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (void*,unsigned long) ; 

__attribute__((used)) static void qlcnic_add_lb_filter(struct qlcnic_adapter *adapter,
				 struct sk_buff *skb, int loopback_pkt, u16 vlan_id)
{
	struct ethhdr *phdr = (struct ethhdr *)(skb->data);
	struct qlcnic_filter *fil, *tmp_fil;
	struct hlist_head *head;
	unsigned long time;
	u64 src_addr = 0;
	u8 hindex, op;
	int ret;

	if (!qlcnic_sriov_pf_check(adapter) || (vlan_id == 0xffff))
		vlan_id = 0;

	memcpy(&src_addr, phdr->h_source, ETH_ALEN);
	hindex = qlcnic_mac_hash(src_addr, vlan_id) &
		 (adapter->fhash.fbucket_size - 1);

	if (loopback_pkt) {
		if (adapter->rx_fhash.fnum >= adapter->rx_fhash.fmax)
			return;

		head = &(adapter->rx_fhash.fhead[hindex]);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil) {
			time = tmp_fil->ftime;
			if (time_after(jiffies, QLCNIC_READD_AGE * HZ + time))
				tmp_fil->ftime = jiffies;
			return;
		}

		fil = kzalloc(sizeof(struct qlcnic_filter), GFP_ATOMIC);
		if (!fil)
			return;

		fil->ftime = jiffies;
		memcpy(fil->faddr, &src_addr, ETH_ALEN);
		fil->vlan_id = vlan_id;
		spin_lock(&adapter->rx_mac_learn_lock);
		hlist_add_head(&(fil->fnode), head);
		adapter->rx_fhash.fnum++;
		spin_unlock(&adapter->rx_mac_learn_lock);
	} else {
		head = &adapter->fhash.fhead[hindex];

		spin_lock(&adapter->mac_learn_lock);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil) {
			op = vlan_id ? QLCNIC_MAC_VLAN_DEL : QLCNIC_MAC_DEL;
			ret = qlcnic_sre_macaddr_change(adapter,
							(u8 *)&src_addr,
							vlan_id, op);
			if (!ret) {
				hlist_del(&tmp_fil->fnode);
				adapter->fhash.fnum--;
			}

			spin_unlock(&adapter->mac_learn_lock);

			return;
		}

		spin_unlock(&adapter->mac_learn_lock);

		head = &adapter->rx_fhash.fhead[hindex];

		spin_lock(&adapter->rx_mac_learn_lock);

		tmp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		if (tmp_fil)
			qlcnic_delete_rx_list_mac(adapter, tmp_fil, &src_addr,
						  vlan_id);

		spin_unlock(&adapter->rx_mac_learn_lock);
	}
}