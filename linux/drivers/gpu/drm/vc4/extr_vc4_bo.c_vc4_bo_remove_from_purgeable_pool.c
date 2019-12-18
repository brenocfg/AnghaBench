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
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct vc4_dev {TYPE_3__ purgeable; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct vc4_bo {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_bo_remove_from_purgeable_pool_locked (struct vc4_bo*) ; 

void vc4_bo_remove_from_purgeable_pool(struct vc4_bo *bo)
{
	struct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	mutex_lock(&vc4->purgeable.lock);
	vc4_bo_remove_from_purgeable_pool_locked(bo);
	mutex_unlock(&vc4->purgeable.lock);
}