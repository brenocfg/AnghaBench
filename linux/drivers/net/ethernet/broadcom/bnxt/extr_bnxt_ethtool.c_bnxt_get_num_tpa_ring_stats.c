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
struct bnxt {scalar_t__ max_tpa_v2; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BNXT_SUPPORTS_TPA (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ring_tpa2_stats_str ; 
 int /*<<< orphan*/  bnxt_ring_tpa_stats_str ; 

__attribute__((used)) static int bnxt_get_num_tpa_ring_stats(struct bnxt *bp)
{
	if (BNXT_SUPPORTS_TPA(bp)) {
		if (bp->max_tpa_v2)
			return ARRAY_SIZE(bnxt_ring_tpa2_stats_str);
		return ARRAY_SIZE(bnxt_ring_tpa_stats_str);
	}
	return 0;
}