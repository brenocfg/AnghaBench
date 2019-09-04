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
struct ttm_buffer_object {int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  reservation_object_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_add_to_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 

void ttm_bo_move_to_lru_tail(struct ttm_buffer_object *bo)
{
	reservation_object_assert_held(bo->resv);

	ttm_bo_del_from_lru(bo);
	ttm_bo_add_to_lru(bo);
}