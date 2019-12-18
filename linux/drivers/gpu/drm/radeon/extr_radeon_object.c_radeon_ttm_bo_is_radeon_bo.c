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
struct ttm_buffer_object {int /*<<< orphan*/ * destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_ttm_bo_destroy ; 

bool radeon_ttm_bo_is_radeon_bo(struct ttm_buffer_object *bo)
{
	if (bo->destroy == &radeon_ttm_bo_destroy)
		return true;
	return false;
}