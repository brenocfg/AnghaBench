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
struct ttm_lru_bulk_move_pos {struct ttm_buffer_object* last; struct ttm_buffer_object* first; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ttm_bo_bulk_move_set_pos(struct ttm_lru_bulk_move_pos *pos,
				     struct ttm_buffer_object *bo)
{
	if (!pos->first)
		pos->first = bo;
	pos->last = bo;
}