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
struct rtllib_device {int mgmt_queue_head; struct sk_buff** mgmt_queue_ring; } ;

/* Variables and functions */
 int MGMT_QUEUE_NUM ; 

__attribute__((used)) static void enqueue_mgmt(struct rtllib_device *ieee, struct sk_buff *skb)
{
	int nh;

	nh = (ieee->mgmt_queue_head + 1) % MGMT_QUEUE_NUM;

/* if the queue is full but we have newer frames then
 * just overwrites the oldest.
 *
 * if (nh == ieee->mgmt_queue_tail)
 *		return -1;
 */
	ieee->mgmt_queue_head = nh;
	ieee->mgmt_queue_ring[nh] = skb;

}