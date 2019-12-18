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
typedef  int /*<<< orphan*/  u32 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct peak_time_ref {int dummy; } ;

/* Variables and functions */
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  peak_usb_get_ts_time (struct peak_time_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

int peak_usb_netif_rx(struct sk_buff *skb,
		      struct peak_time_ref *time_ref, u32 ts_low)
{
	struct skb_shared_hwtstamps *hwts = skb_hwtstamps(skb);

	peak_usb_get_ts_time(time_ref, ts_low, &hwts->hwtstamp);

	return netif_rx(skb);
}