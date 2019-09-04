#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {TYPE_2__* resv; } ;
struct amdgpu_bo {int /*<<< orphan*/  tiling_flags; TYPE_3__ tbo; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {TYPE_1__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void amdgpu_bo_get_tiling_flags(struct amdgpu_bo *bo, u64 *tiling_flags)
{
	lockdep_assert_held(&bo->tbo.resv->lock.base);

	if (tiling_flags)
		*tiling_flags = bo->tiling_flags;
}