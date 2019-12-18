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

/* Variables and functions */
 scalar_t__ EMAC_MTU_OVERHEAD ; 
 scalar_t__ NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 int SKB_DATA_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  emac_rx_size (int) ; 
 int max (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int emac_rx_skb_size(int mtu)
{
	int size = max(mtu + EMAC_MTU_OVERHEAD, emac_rx_size(mtu));

	return SKB_DATA_ALIGN(size + NET_IP_ALIGN) + NET_SKB_PAD;
}