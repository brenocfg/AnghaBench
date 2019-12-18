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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct qlink_tlv_hdr {int /*<<< orphan*/ * val; void* len; void* type; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 struct qlink_tlv_hdr* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static inline void qtnf_cmd_skb_put_tlv_u8(struct sk_buff *skb, u16 tlv_id,
					   u8 value)
{
	struct qlink_tlv_hdr *hdr = skb_put(skb, sizeof(*hdr) + sizeof(value));

	hdr->type = cpu_to_le16(tlv_id);
	hdr->len = cpu_to_le16(sizeof(value));
	*hdr->val = value;
}