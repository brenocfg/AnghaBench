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
struct ttm_buffer_object {int /*<<< orphan*/  ttm_resv; int /*<<< orphan*/ * resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int reservation_object_copy_fences (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttm_bo_individualize_resv(struct ttm_buffer_object *bo)
{
	int r;

	if (bo->resv == &bo->ttm_resv)
		return 0;

	BUG_ON(!reservation_object_trylock(&bo->ttm_resv));

	r = reservation_object_copy_fences(&bo->ttm_resv, bo->resv);
	if (r)
		reservation_object_unlock(&bo->ttm_resv);

	return r;
}