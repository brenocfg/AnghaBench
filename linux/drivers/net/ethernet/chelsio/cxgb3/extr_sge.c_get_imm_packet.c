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
struct rsp_desc {int /*<<< orphan*/  imm_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IMMED_PKT_SIZE ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *get_imm_packet(const struct rsp_desc *resp)
{
	struct sk_buff *skb = alloc_skb(IMMED_PKT_SIZE, GFP_ATOMIC);

	if (skb) {
		__skb_put(skb, IMMED_PKT_SIZE);
		skb_copy_to_linear_data(skb, resp->imm_data, IMMED_PKT_SIZE);
	}
	return skb;
}