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
struct bnxt {int dummy; } ;

/* Variables and functions */
 unsigned int bnxt_get_func_stat_ctxs (struct bnxt*) ; 
 unsigned int bnxt_get_max_func_stat_ctxs (struct bnxt*) ; 

unsigned int bnxt_get_avail_stat_ctxs_for_en(struct bnxt *bp)
{
	return bnxt_get_max_func_stat_ctxs(bp) - bnxt_get_func_stat_ctxs(bp);
}