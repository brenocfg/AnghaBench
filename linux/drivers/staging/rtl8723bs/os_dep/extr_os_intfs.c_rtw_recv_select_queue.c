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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct iphdr {int tos; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
#define  ETH_P_IP 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rtw_1d_to_queue ; 

u16 rtw_recv_select_queue(struct sk_buff *skb)
{
	struct iphdr *piphdr;
	unsigned int dscp;
	__be16	eth_type;
	u32 priority;
	u8 *pdata = skb->data;

	memcpy(&eth_type, pdata + (ETH_ALEN << 1), 2);

	switch (be16_to_cpu(eth_type)) {
		case ETH_P_IP:

			piphdr = (struct iphdr *)(pdata + ETH_HLEN);

			dscp = piphdr->tos & 0xfc;

			priority = dscp >> 5;

			break;
		default:
			priority = 0;
	}

	return rtw_1d_to_queue[priority];
}