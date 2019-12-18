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
typedef  scalar_t__ u16 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_BUFFER_SIZE ; 
 struct sk_buff* ath6kl_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 

__attribute__((used)) static void ath6kl_alloc_netbufs(struct sk_buff_head *q, u16 num)
{
	struct sk_buff *skb;

	while (num) {
		skb = ath6kl_buf_alloc(ATH6KL_BUFFER_SIZE);
		if (!skb) {
			ath6kl_err("netbuf allocation failed\n");
			return;
		}
		skb_queue_tail(q, skb);
		num--;
	}
}