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
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,char const*,int) ; 

__attribute__((used)) static void bcsp_slip_msgdelim(struct sk_buff *skb)
{
	const char pkt_delim = 0xc0;

	skb_put_data(skb, &pkt_delim, 1);
}