#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {scalar_t__ state; TYPE_2__* bdev; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ttm_tt_unpopulate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_unpopulated ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_tt_clear_mapping (struct ttm_tt*) ; 

void ttm_tt_unpopulate(struct ttm_tt *ttm)
{
	if (ttm->state == tt_unpopulated)
		return;

	ttm_tt_clear_mapping(ttm);
	if (ttm->bdev->driver->ttm_tt_unpopulate)
		ttm->bdev->driver->ttm_tt_unpopulate(ttm);
	else
		ttm_pool_unpopulate(ttm);
}