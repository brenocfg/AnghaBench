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
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* qeth_dst_check_rcu (struct sk_buff*,int) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 int qeth_l3_get_cast_type_rcu (struct sk_buff*,struct dst_entry*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int qeth_l3_get_cast_type(struct sk_buff *skb)
{
	int ipv = qeth_get_ip_version(skb);
	struct dst_entry *dst;
	int cast_type;

	rcu_read_lock();
	dst = qeth_dst_check_rcu(skb, ipv);
	cast_type = qeth_l3_get_cast_type_rcu(skb, dst, ipv);
	rcu_read_unlock();

	return cast_type;
}