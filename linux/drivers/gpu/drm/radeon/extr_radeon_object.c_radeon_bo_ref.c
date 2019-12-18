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
struct radeon_bo {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_get (int /*<<< orphan*/ *) ; 

struct radeon_bo *radeon_bo_ref(struct radeon_bo *bo)
{
	if (bo == NULL)
		return NULL;

	ttm_bo_get(&bo->tbo);
	return bo;
}