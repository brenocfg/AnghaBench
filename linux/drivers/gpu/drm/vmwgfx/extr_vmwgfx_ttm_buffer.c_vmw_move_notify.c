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
struct ttm_mem_reg {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_bo_move_notify (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  vmw_query_move_notify (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 

__attribute__((used)) static void vmw_move_notify(struct ttm_buffer_object *bo,
			    bool evict,
			    struct ttm_mem_reg *mem)
{
	vmw_bo_move_notify(bo, mem);
	vmw_query_move_notify(bo, mem);
}