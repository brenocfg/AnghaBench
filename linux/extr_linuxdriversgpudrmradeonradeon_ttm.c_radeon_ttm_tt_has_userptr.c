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
struct ttm_tt {int dummy; } ;
struct radeon_ttm_tt {int /*<<< orphan*/  userptr; } ;

/* Variables and functions */
 struct radeon_ttm_tt* radeon_ttm_tt_to_gtt (struct ttm_tt*) ; 

bool radeon_ttm_tt_has_userptr(struct ttm_tt *ttm)
{
	struct radeon_ttm_tt *gtt = radeon_ttm_tt_to_gtt(ttm);

	if (gtt == NULL)
		return false;

	return !!gtt->userptr;
}