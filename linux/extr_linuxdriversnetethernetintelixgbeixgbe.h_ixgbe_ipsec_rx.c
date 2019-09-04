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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct sk_buff {int dummy; } ;
struct ixgbe_ring {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ixgbe_ipsec_rx(struct ixgbe_ring *rx_ring,
				  union ixgbe_adv_rx_desc *rx_desc,
				  struct sk_buff *skb) { }