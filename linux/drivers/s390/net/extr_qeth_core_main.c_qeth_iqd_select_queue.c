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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_IQD_MCAST_TXQ ; 
 int /*<<< orphan*/  QETH_IQD_MIN_UCAST_TXQ ; 
 scalar_t__ RTN_UNICAST ; 

u16 qeth_iqd_select_queue(struct net_device *dev, struct sk_buff *skb,
			  u8 cast_type, struct net_device *sb_dev)
{
	if (cast_type != RTN_UNICAST)
		return QETH_IQD_MCAST_TXQ;
	return QETH_IQD_MIN_UCAST_TXQ;
}