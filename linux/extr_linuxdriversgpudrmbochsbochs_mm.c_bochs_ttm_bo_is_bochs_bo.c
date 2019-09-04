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
 int /*<<< orphan*/  bochs_bo_ttm_destroy ; 

__attribute__((used)) static bool bochs_ttm_bo_is_bochs_bo(struct ttm_buffer_object *bo)
{
	if (bo->destroy == &bochs_bo_ttm_destroy)
		return true;
	return false;
}