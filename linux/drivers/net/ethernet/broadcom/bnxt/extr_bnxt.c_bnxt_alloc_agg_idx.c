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
typedef  size_t u16 ;
struct bnxt_tpa_idx_map {size_t* agg_id_tbl; int /*<<< orphan*/  agg_idx_bmap; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_idx_map* rx_tpa_idx_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_AGG_IDX_BMAP_SIZE ; 
 size_t MAX_TPA_P5_MASK ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 bnxt_alloc_agg_idx(struct bnxt_rx_ring_info *rxr, u16 agg_id)
{
	struct bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;
	u16 idx = agg_id & MAX_TPA_P5_MASK;

	if (test_bit(idx, map->agg_idx_bmap))
		idx = find_first_zero_bit(map->agg_idx_bmap,
					  BNXT_AGG_IDX_BMAP_SIZE);
	__set_bit(idx, map->agg_idx_bmap);
	map->agg_id_tbl[agg_id] = idx;
	return idx;
}