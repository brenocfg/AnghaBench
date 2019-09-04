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
typedef  scalar_t__ u16 ;
struct bnxt_rx_ring_info {scalar_t__ rx_agg_bmap_size; int /*<<< orphan*/  rx_agg_bmap; } ;

/* Variables and functions */
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ find_next_zero_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u16 bnxt_find_next_agg_idx(struct bnxt_rx_ring_info *rxr, u16 idx)
{
	u16 next, max = rxr->rx_agg_bmap_size;

	next = find_next_zero_bit(rxr->rx_agg_bmap, max, idx);
	if (next >= max)
		next = find_first_zero_bit(rxr->rx_agg_bmap, max);
	return next;
}