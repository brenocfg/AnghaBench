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
struct bnxt_tpa_info {struct rx_agg_cmp* agg_arr; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_info* rx_tpa; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct rx_agg_cmp *bnxt_get_tpa_agg_p5(struct bnxt *bp,
					      struct bnxt_rx_ring_info *rxr,
					      u16 agg_id, u16 curr)
{
	struct bnxt_tpa_info *tpa_info = &rxr->rx_tpa[agg_id];

	return &tpa_info->agg_arr[curr];
}