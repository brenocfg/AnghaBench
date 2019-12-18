#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets_csum; } ;
struct emac_instance {TYPE_1__ stats; scalar_t__ tah_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 

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