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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct emac_instance {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void emac_rx_csum(struct emac_instance *dev,
				struct sk_buff *skb, u16 ctrl)
{
#ifdef CONFIG_IBM_EMAC_TAH
	if (!ctrl && dev->tah_dev) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		++dev->stats.rx_packets_csum;
	}
#endif
}