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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_accel_dropped_pkts ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 

__attribute__((used)) static void drop_packet(struct sk_buff *skb)
{
	atomic_inc(&cm_accel_dropped_pkts);
	dev_kfree_skb_any(skb);
}