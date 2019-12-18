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
struct rx_agg_cmp {int dummy; } ;
struct bnxt_tpa_info {scalar_t__ agg_count; struct rx_agg_cmp* agg_arr; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_info* rx_tpa; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 size_t TPA_AGG_AGG_ID (struct rx_agg_cmp*) ; 
 size_t bnxt_lookup_agg_idx (struct bnxt_rx_ring_info*,size_t) ; 

__attribute__((used)) static void bnxt_tpa_agg(struct bnxt *bp, struct bnxt_rx_ring_info *rxr,
			 struct rx_agg_cmp *rx_agg)
{
	u16 agg_id = TPA_AGG_AGG_ID(rx_agg);
	struct bnxt_tpa_info *tpa_info;

	agg_id = bnxt_lookup_agg_idx(rxr, agg_id);
	tpa_info = &rxr->rx_tpa[agg_id];
	BUG_ON(tpa_info->agg_count >= MAX_SKB_FRAGS);
	tpa_info->agg_arr[tpa_info->agg_count++] = *rx_agg;
}