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
struct htc_packet {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HTC_CONTROL_BUFFER_SIZE ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct htc_packet*) ; 
 struct htc_packet* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct htc_packet *build_htc_txctrl_packet(void)
{
	struct htc_packet *packet = NULL;
	struct sk_buff *skb;

	packet = kzalloc(sizeof(struct htc_packet), GFP_KERNEL);
	if (packet == NULL)
		return NULL;

	skb = __dev_alloc_skb(HTC_CONTROL_BUFFER_SIZE, GFP_KERNEL);

	if (skb == NULL) {
		kfree(packet);
		return NULL;
	}
	packet->skb = skb;

	return packet;
}