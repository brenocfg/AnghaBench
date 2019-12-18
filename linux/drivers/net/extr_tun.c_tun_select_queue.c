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
typedef  int /*<<< orphan*/  u16 ;
struct tun_struct {int /*<<< orphan*/  steering_prog; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tun_struct* netdev_priv (struct net_device*) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tun_automq_select_queue (struct tun_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  tun_ebpf_select_queue (struct tun_struct*,struct sk_buff*) ; 

__attribute__((used)) static u16 tun_select_queue(struct net_device *dev, struct sk_buff *skb,
			    struct net_device *sb_dev)
{
	struct tun_struct *tun = netdev_priv(dev);
	u16 ret;

	rcu_read_lock();
	if (rcu_dereference(tun->steering_prog))
		ret = tun_ebpf_select_queue(tun, skb);
	else
		ret = tun_automq_select_queue(tun, skb);
	rcu_read_unlock();

	return ret;
}