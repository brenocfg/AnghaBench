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
struct sk_buff {int /*<<< orphan*/  cb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtllib_xmit_inter (struct sk_buff*,struct net_device*) ; 

int rtllib_xmit(struct sk_buff *skb, struct net_device *dev)
{
	memset(skb->cb, 0, sizeof(skb->cb));
	return rtllib_xmit_inter(skb, dev);
}