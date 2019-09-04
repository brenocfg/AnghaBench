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
struct ixgbe_tx_buffer {int dummy; } ;
struct ixgbe_ring {int dummy; } ;
struct ixgbe_ipsec_tx_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ixgbe_ipsec_tx(struct ixgbe_ring *tx_ring,
				 struct ixgbe_tx_buffer *first,
				 struct ixgbe_ipsec_tx_data *itd) { return 0; }