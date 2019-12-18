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
struct ttm_buffer_object {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_add_mem_to_lru (struct ttm_buffer_object*,int /*<<< orphan*/ *) ; 

void ttm_bo_add_to_lru(struct ttm_buffer_object *bo)
{
	ttm_bo_add_mem_to_lru(bo, &bo->mem);
}