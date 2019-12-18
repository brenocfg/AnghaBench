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
struct bnxt_tpa_idx_map {int /*<<< orphan*/  agg_idx_bmap; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_idx_map* rx_tpa_idx_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_free_agg_idx(struct bnxt_rx_ring_info *rxr, u16 idx)
{
	struct bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;

	__clear_bit(idx, map->agg_idx_bmap);
}