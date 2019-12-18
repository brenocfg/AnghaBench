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
struct ttm_tt {scalar_t__ state; } ;
struct ttm_operation_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ tt_unpopulated ; 
 int ttm_pool_populate (struct ttm_tt*,struct ttm_operation_ctx*) ; 

int ttm_agp_tt_populate(struct ttm_tt *ttm, struct ttm_operation_ctx *ctx)
{
	if (ttm->state != tt_unpopulated)
		return 0;

	return ttm_pool_populate(ttm, ctx);
}