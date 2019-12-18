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
struct bnxt_tpa_idx_map {size_t* agg_id_tbl; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_idx_map* rx_tpa_idx_map; } ;

/* Variables and functions */

__attribute__((used)) static u16 bnxt_lookup_agg_idx(struct bnxt_rx_ring_info *rxr, u16 agg_id)
{
	struct bnxt_tpa_idx_map *map = rxr->rx_tpa_idx_map;

	return map->agg_id_tbl[agg_id];
}