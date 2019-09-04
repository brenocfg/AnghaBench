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
struct hinic_sge {int dummy; } ;
struct hinic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_unmap_skb (struct hinic_dev*,struct sk_buff*,struct hinic_sge*) ; 

__attribute__((used)) static void tx_free_skb(struct hinic_dev *nic_dev, struct sk_buff *skb,
			struct hinic_sge *sges)
{
	tx_unmap_skb(nic_dev, skb, sges);

	dev_kfree_skb_any(skb);
}