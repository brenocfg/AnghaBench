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

/* Variables and functions */
 int /*<<< orphan*/  __ppp_decompress_proto (struct sk_buff*) ; 
 int pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static bool ppp_decompress_proto(struct sk_buff *skb)
{
	/* At least one byte should be present (if protocol is compressed) */
	if (!pskb_may_pull(skb, 1))
		return false;

	__ppp_decompress_proto(skb);

	/* Protocol field should occupy 2 bytes when not compressed */
	return pskb_may_pull(skb, 2);
}