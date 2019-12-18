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
typedef  size_t u32 ;
struct sk_buff {unsigned char* data; size_t len; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_packets; } ;
struct hns3_enet_tqp_vector {TYPE_1__ rx_group; } ;
struct hns3_enet_ring {struct hns3_enet_tqp_vector* tqp_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned char*,size_t,int) ; 

__attribute__((used)) static void hns3_lb_check_skb_data(struct hns3_enet_ring *ring,
				   struct sk_buff *skb)
{
	struct hns3_enet_tqp_vector *tqp_vector = ring->tqp_vector;
	unsigned char *packet = skb->data;
	u32 i;

	for (i = 0; i < skb->len; i++)
		if (packet[i] != (unsigned char)(i & 0xff))
			break;

	/* The packet is correctly received */
	if (i == skb->len)
		tqp_vector->rx_group.total_packets++;
	else
		print_hex_dump(KERN_ERR, "selftest:", DUMP_PREFIX_OFFSET, 16, 1,
			       skb->data, skb->len, true);

	dev_kfree_skb_any(skb);
}