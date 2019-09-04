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
struct net_device {int dummy; } ;
struct e1000_tx_ring {int dummy; } ;

/* Variables and functions */
 int E1000_DESC_UNUSED (struct e1000_tx_ring*) ; 
 int __e1000_maybe_stop_tx (struct net_device*,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int e1000_maybe_stop_tx(struct net_device *netdev,
			       struct e1000_tx_ring *tx_ring, int size)
{
	if (likely(E1000_DESC_UNUSED(tx_ring) >= size))
		return 0;
	return __e1000_maybe_stop_tx(netdev, size);
}