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
struct vlan_ethhdr {scalar_t__ h_vlan_proto; } ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct iphdr {int /*<<< orphan*/  tot_len; } ;
struct be_wrb_params {int /*<<< orphan*/  features; } ;
struct be_adapter {scalar_t__ qnq_vid; scalar_t__ pvid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_WRB_F_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int ETH_HLEN ; 
 scalar_t__ ETH_P_8021Q ; 
 unsigned int VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  VLAN_SKIP_HW ; 
 struct sk_buff* be_insert_vlan_in_pkt (struct be_adapter*,struct sk_buff*,struct be_wrb_params*) ; 
 scalar_t__ be_ipv6_tx_stall_chk (struct be_adapter*,struct sk_buff*) ; 
 scalar_t__ be_pvid_tagging_enabled (struct be_adapter*) ; 
 scalar_t__ be_vlan_tag_tx_chk (struct be_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ ip_hdr (struct sk_buff*) ; 
 scalar_t__ is_ipv4_pkt (struct sk_buff*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  qnq_async_evt_rcvd (struct be_adapter*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *be_lancer_xmit_workarounds(struct be_adapter *adapter,
						  struct sk_buff *skb,
						  struct be_wrb_params
						  *wrb_params)
{
	struct vlan_ethhdr *veh = (struct vlan_ethhdr *)skb->data;
	unsigned int eth_hdr_len;
	struct iphdr *ip;

	/* For padded packets, BE HW modifies tot_len field in IP header
	 * incorrecly when VLAN tag is inserted by HW.
	 * For padded packets, Lancer computes incorrect checksum.
	 */
	eth_hdr_len = ntohs(skb->protocol) == ETH_P_8021Q ?
						VLAN_ETH_HLEN : ETH_HLEN;
	if (skb->len <= 60 &&
	    (lancer_chip(adapter) || skb_vlan_tag_present(skb)) &&
	    is_ipv4_pkt(skb)) {
		ip = (struct iphdr *)ip_hdr(skb);
		pskb_trim(skb, eth_hdr_len + ntohs(ip->tot_len));
	}

	/* If vlan tag is already inlined in the packet, skip HW VLAN
	 * tagging in pvid-tagging mode
	 */
	if (be_pvid_tagging_enabled(adapter) &&
	    veh->h_vlan_proto == htons(ETH_P_8021Q))
		BE_WRB_F_SET(wrb_params->features, VLAN_SKIP_HW, 1);

	/* HW has a bug wherein it will calculate CSUM for VLAN
	 * pkts even though it is disabled.
	 * Manually insert VLAN in pkt.
	 */
	if (skb->ip_summed != CHECKSUM_PARTIAL &&
	    skb_vlan_tag_present(skb)) {
		skb = be_insert_vlan_in_pkt(adapter, skb, wrb_params);
		if (unlikely(!skb))
			goto err;
	}

	/* HW may lockup when VLAN HW tagging is requested on
	 * certain ipv6 packets. Drop such pkts if the HW workaround to
	 * skip HW tagging is not enabled by FW.
	 */
	if (unlikely(be_ipv6_tx_stall_chk(adapter, skb) &&
		     (adapter->pvid || adapter->qnq_vid) &&
		     !qnq_async_evt_rcvd(adapter)))
		goto tx_drop;

	/* Manual VLAN tag insertion to prevent:
	 * ASIC lockup when the ASIC inserts VLAN tag into
	 * certain ipv6 packets. Insert VLAN tags in driver,
	 * and set event, completion, vlan bits accordingly
	 * in the Tx WRB.
	 */
	if (be_ipv6_tx_stall_chk(adapter, skb) &&
	    be_vlan_tag_tx_chk(adapter, skb)) {
		skb = be_insert_vlan_in_pkt(adapter, skb, wrb_params);
		if (unlikely(!skb))
			goto err;
	}

	return skb;
tx_drop:
	dev_kfree_skb_any(skb);
err:
	return NULL;
}