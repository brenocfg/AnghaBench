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
struct bnxt {int flags; unsigned int rx_nr_rings; unsigned int tx_nr_rings; unsigned int cp_nr_rings; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 unsigned int bnxt_get_max_func_cp_rings_for_en (struct bnxt*) ; 

unsigned int bnxt_get_avail_cp_rings_for_en(struct bnxt *bp)
{
	unsigned int cp;

	cp = bnxt_get_max_func_cp_rings_for_en(bp);
	if (bp->flags & BNXT_FLAG_CHIP_P5)
		return cp - bp->rx_nr_rings - bp->tx_nr_rings;
	else
		return cp - bp->cp_nr_rings;
}