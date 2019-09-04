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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ port_info; } ;
struct metadata_dst {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ METADATA_HW_PORT_MUX ; 
 int /*<<< orphan*/  NFP_NET_META_PORTID ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int skb_cow_head (struct sk_buff*,int) ; 
 struct metadata_dst* skb_metadata_dst (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nfp_net_prep_port_id(struct sk_buff *skb)
{
	struct metadata_dst *md_dst = skb_metadata_dst(skb);
	unsigned char *data;

	if (likely(!md_dst))
		return 0;
	if (unlikely(md_dst->type != METADATA_HW_PORT_MUX))
		return 0;

	if (unlikely(skb_cow_head(skb, 8)))
		return -ENOMEM;

	data = skb_push(skb, 8);
	put_unaligned_be32(NFP_NET_META_PORTID, data);
	put_unaligned_be32(md_dst->u.port_info.port_id, data + 4);

	return 8;
}