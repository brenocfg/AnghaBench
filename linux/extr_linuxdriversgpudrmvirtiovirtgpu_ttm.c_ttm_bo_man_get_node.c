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
struct ttm_place {int dummy; } ;
struct ttm_mem_type_manager {int dummy; } ;
struct ttm_mem_reg {void* mm_node; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ttm_bo_man_get_node(struct ttm_mem_type_manager *man,
			       struct ttm_buffer_object *bo,
			       const struct ttm_place *place,
			       struct ttm_mem_reg *mem)
{
	mem->mm_node = (void *)1;
	return 0;
}