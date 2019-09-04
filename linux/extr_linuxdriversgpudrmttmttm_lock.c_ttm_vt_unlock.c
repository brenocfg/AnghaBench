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
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {TYPE_1__ hash; } ;
struct ttm_lock {TYPE_2__ base; int /*<<< orphan*/  vt_holder; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_REF_USAGE ; 
 int ttm_ref_object_base_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ttm_vt_unlock(struct ttm_lock *lock)
{
	return ttm_ref_object_base_unref(lock->vt_holder,
					 lock->base.hash.key, TTM_REF_USAGE);
}