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
struct intel_uncore_box {TYPE_3__* pmu; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__* type; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_box ) (struct intel_uncore_box*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UNCORE_BOX_FLAG_INITIATED ; 
 int /*<<< orphan*/  stub1 (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void uncore_box_init(struct intel_uncore_box *box)
{
	if (!test_and_set_bit(UNCORE_BOX_FLAG_INITIATED, &box->flags)) {
		if (box->pmu->type->ops->init_box)
			box->pmu->type->ops->init_box(box);
	}
}