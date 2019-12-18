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
struct rt6_info {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* dst_check (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_get_cookie (struct rt6_info*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static inline struct dst_entry *qeth_dst_check_rcu(struct sk_buff *skb, int ipv)
{
	struct dst_entry *dst = skb_dst(skb);
	struct rt6_info *rt;

	rt = (struct rt6_info *) dst;
	if (dst)
		dst = dst_check(dst, (ipv == 6) ? rt6_get_cookie(rt) : 0);
	return dst;
}