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
struct bnxt {int cp_nr_rings; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int bnxt_get_num_tpa_ring_stats (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ring_stats_str ; 
 int /*<<< orphan*/  bnxt_ring_sw_stats_str ; 

__attribute__((used)) static int bnxt_get_num_ring_stats(struct bnxt *bp)
{
	int num_stats;

	num_stats = ARRAY_SIZE(bnxt_ring_stats_str) +
		    ARRAY_SIZE(bnxt_ring_sw_stats_str) +
		    bnxt_get_num_tpa_ring_stats(bp);
	return num_stats * bp->cp_nr_rings;
}