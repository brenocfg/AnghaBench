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
struct sk_buff {int dummy; } ;
struct pkt_attrib {int ether_type; int priority; int /*<<< orphan*/  subtype; int /*<<< orphan*/  hdrlen; } ;
struct iphdr {int tos; } ;
typedef  int /*<<< orphan*/  ip_hdr ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int ETH_P_PAE ; 
 int /*<<< orphan*/  WIFI_QOS_DATA_TYPE ; 
 int /*<<< orphan*/  WLAN_HDR_A3_QOS_LEN ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,struct iphdr*,int) ; 

__attribute__((used)) static void set_qos(struct sk_buff *skb, struct pkt_attrib *pattrib)
{
	if (pattrib->ether_type == 0x0800) {
		struct iphdr ip_hdr;

		skb_copy_bits(skb, ETH_HLEN, &ip_hdr, sizeof(ip_hdr));
		pattrib->priority = ip_hdr.tos >> 5;
	} else if (pattrib->ether_type == ETH_P_PAE) {
		/* When priority processing of data frames is supported,
		 * a STA's SME should send EAPOL-Key frames at the highest
		 * priority.
		 */
		pattrib->priority = 7;
	} else {
		pattrib->priority = 0;
	}

	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
}