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
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 

void ttm_bo_unref(struct ttm_buffer_object **p_bo)
{
	struct ttm_buffer_object *bo = *p_bo;

	*p_bo = NULL;
	ttm_bo_put(bo);
}