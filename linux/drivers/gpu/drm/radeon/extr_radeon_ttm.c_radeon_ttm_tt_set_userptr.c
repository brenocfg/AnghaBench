#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int dummy; } ;
struct radeon_ttm_tt {int /*<<< orphan*/  userflags; int /*<<< orphan*/  usermm; int /*<<< orphan*/  userptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* current ; 
 struct radeon_ttm_tt* radeon_ttm_tt_to_gtt (struct ttm_tt*) ; 

int radeon_ttm_tt_set_userptr(struct ttm_tt *ttm, uint64_t addr,
			      uint32_t flags)
{
	struct radeon_ttm_tt *gtt = radeon_ttm_tt_to_gtt(ttm);

	if (gtt == NULL)
		return -EINVAL;

	gtt->userptr = addr;
	gtt->usermm = current->mm;
	gtt->userflags = flags;
	return 0;
}