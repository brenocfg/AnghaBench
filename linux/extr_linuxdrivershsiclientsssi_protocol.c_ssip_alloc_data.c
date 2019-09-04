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
struct ssi_protocol {int /*<<< orphan*/  channel_id_data; } ;
struct sk_buff {int dummy; } ;
struct hsi_msg {struct sk_buff* context; int /*<<< orphan*/  channel; int /*<<< orphan*/  destructor; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {scalar_t__ nr_frags; } ;

/* Variables and functions */
 struct hsi_msg* hsi_alloc_msg (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  ssip_free_data ; 
 int /*<<< orphan*/  ssip_skb_to_msg (struct sk_buff*,struct hsi_msg*) ; 

__attribute__((used)) static struct hsi_msg *ssip_alloc_data(struct ssi_protocol *ssi,
					struct sk_buff *skb, gfp_t flags)
{
	struct hsi_msg *msg;

	msg = hsi_alloc_msg(skb_shinfo(skb)->nr_frags + 1, flags);
	if (!msg)
		return NULL;
	ssip_skb_to_msg(skb, msg);
	msg->destructor = ssip_free_data;
	msg->channel = ssi->channel_id_data;
	msg->context = skb;

	return msg;
}