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
struct vc4_dev {int /*<<< orphan*/  bo_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct vc4_bo {int /*<<< orphan*/  size_head; int /*<<< orphan*/  unref_head; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_bo_remove_from_cache(struct vc4_bo *bo)
{
	struct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	lockdep_assert_held(&vc4->bo_lock);
	list_del(&bo->unref_head);
	list_del(&bo->size_head);
}