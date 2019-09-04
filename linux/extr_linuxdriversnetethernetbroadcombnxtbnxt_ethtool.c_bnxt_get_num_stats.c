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
struct bnxt {int cp_nr_rings; int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_PORT_STATS ; 
 int BNXT_FLAG_PORT_STATS_EXT ; 
 scalar_t__ BNXT_NUM_PORT_STATS ; 
 scalar_t__ BNXT_NUM_PORT_STATS_EXT ; 
 int BNXT_NUM_STATS ; 
 scalar_t__ BNXT_NUM_SW_FUNC_STATS ; 

__attribute__((used)) static int bnxt_get_num_stats(struct bnxt *bp)
{
	int num_stats = BNXT_NUM_STATS * bp->cp_nr_rings;

	num_stats += BNXT_NUM_SW_FUNC_STATS;

	if (bp->flags & BNXT_FLAG_PORT_STATS)
		num_stats += BNXT_NUM_PORT_STATS;

	if (bp->flags & BNXT_FLAG_PORT_STATS_EXT)
		num_stats += BNXT_NUM_PORT_STATS_EXT;

	return num_stats;
}