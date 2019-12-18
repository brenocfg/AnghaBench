#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int max_stat_ctxs; } ;
struct bnxt {TYPE_1__ hw_resc; } ;

/* Variables and functions */

unsigned int bnxt_get_max_func_stat_ctxs(struct bnxt *bp)
{
	return bp->hw_resc.max_stat_ctxs;
}