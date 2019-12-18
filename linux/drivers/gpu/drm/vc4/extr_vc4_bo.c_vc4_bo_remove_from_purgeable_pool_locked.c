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
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  num; } ;
struct vc4_dev {TYPE_1__ purgeable; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct vc4_bo {TYPE_3__ base; int /*<<< orphan*/  size_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_bo_remove_from_purgeable_pool_locked(struct vc4_bo *bo)
{
	struct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	/* list_del_init() is used here because the caller might release
	 * the purgeable lock in order to acquire the madv one and update the
	 * madv status.
	 * During this short period of time a user might decide to mark
	 * the BO as unpurgeable, and if bo->madv is set to
	 * VC4_MADV_DONTNEED it will try to remove the BO from the
	 * purgeable list which will fail if the ->next/prev fields
	 * are set to LIST_POISON1/LIST_POISON2 (which is what
	 * list_del() does).
	 * Re-initializing the list element guarantees that list_del()
	 * will work correctly even if it's a NOP.
	 */
	list_del_init(&bo->size_head);
	vc4->purgeable.num--;
	vc4->purgeable.size -= bo->base.base.size;
}