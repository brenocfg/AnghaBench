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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *fza_alloc_skb(struct net_device *dev,
					    unsigned int length)
{
	return __netdev_alloc_skb(dev, length, GFP_KERNEL);
}