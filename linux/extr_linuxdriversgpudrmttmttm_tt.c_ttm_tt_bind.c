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
struct ttm_tt {scalar_t__ state; TYPE_1__* func; } ;
struct ttm_operation_ctx {int dummy; } ;
struct ttm_mem_reg {int dummy; } ;
struct TYPE_2__ {int (* bind ) (struct ttm_tt*,struct ttm_mem_reg*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct ttm_tt*,struct ttm_mem_reg*) ; 
 scalar_t__ tt_bound ; 
 int ttm_tt_populate (struct ttm_tt*,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_tt_bind(struct ttm_tt *ttm, struct ttm_mem_reg *bo_mem,
		struct ttm_operation_ctx *ctx)
{
	int ret = 0;

	if (!ttm)
		return -EINVAL;

	if (ttm->state == tt_bound)
		return 0;

	ret = ttm_tt_populate(ttm, ctx);
	if (ret)
		return ret;

	ret = ttm->func->bind(ttm, bo_mem);
	if (unlikely(ret != 0))
		return ret;

	ttm->state = tt_bound;

	return 0;
}