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
struct wl1271 {struct sk_buff* dummy_packet; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */

bool wl12xx_is_dummy_packet(struct wl1271 *wl, struct sk_buff *skb)
{
	return wl->dummy_packet == skb;
}