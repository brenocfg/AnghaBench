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
struct rtllib_rx_stats {int dummy; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int rtllib_rx_Mesh(struct rtllib_device *ieee, struct sk_buff *skb,
		 struct rtllib_rx_stats *rx_stats)
{
	return 0;
}