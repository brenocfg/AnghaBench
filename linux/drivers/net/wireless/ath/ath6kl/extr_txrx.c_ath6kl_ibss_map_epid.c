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
typedef  void* u8 ;
typedef  size_t u32 ;
struct wmi_data_hdr {int dummy; } ;
struct sk_buff {void** data; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct ath6kl {size_t node_num; size_t next_ep_id; TYPE_1__* node_map; int /*<<< orphan*/ * tx_pending; } ;
struct TYPE_2__ {void* ep_id; int /*<<< orphan*/  tx_pend; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 void* ENDPOINT_2 ; 
 size_t ENDPOINT_5 ; 
 void* ENDPOINT_UNUSED ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t MAX_NODE_NUM ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ath6kl_ibss_map_epid(struct sk_buff *skb, struct net_device *dev,
			       u32 *map_no)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ethhdr *eth_hdr;
	u32 i, ep_map = -1;
	u8 *datap;

	*map_no = 0;
	datap = skb->data;
	eth_hdr = (struct ethhdr *) (datap + sizeof(struct wmi_data_hdr));

	if (is_multicast_ether_addr(eth_hdr->h_dest))
		return ENDPOINT_2;

	for (i = 0; i < ar->node_num; i++) {
		if (memcmp(eth_hdr->h_dest, ar->node_map[i].mac_addr,
			   ETH_ALEN) == 0) {
			*map_no = i + 1;
			ar->node_map[i].tx_pend++;
			return ar->node_map[i].ep_id;
		}

		if ((ep_map == -1) && !ar->node_map[i].tx_pend)
			ep_map = i;
	}

	if (ep_map == -1) {
		ep_map = ar->node_num;
		ar->node_num++;
		if (ar->node_num > MAX_NODE_NUM)
			return ENDPOINT_UNUSED;
	}

	memcpy(ar->node_map[ep_map].mac_addr, eth_hdr->h_dest, ETH_ALEN);

	for (i = ENDPOINT_2; i <= ENDPOINT_5; i++) {
		if (!ar->tx_pending[i]) {
			ar->node_map[ep_map].ep_id = i;
			break;
		}

		/*
		 * No free endpoint is available, start redistribution on
		 * the inuse endpoints.
		 */
		if (i == ENDPOINT_5) {
			ar->node_map[ep_map].ep_id = ar->next_ep_id;
			ar->next_ep_id++;
			if (ar->next_ep_id > ENDPOINT_5)
				ar->next_ep_id = ENDPOINT_2;
		}
	}

	*map_no = ep_map + 1;
	ar->node_map[ep_map].tx_pend++;

	return ar->node_map[ep_map].ep_id;
}