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
struct perf_event {int dummy; } ;
struct intel_uncore_box {TYPE_3__* pmu; } ;
struct TYPE_6__ {TYPE_2__* type; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_event ) (struct intel_uncore_box*,struct perf_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_uncore_box*,struct perf_event*) ; 

__attribute__((used)) static inline void uncore_disable_event(struct intel_uncore_box *box,
				struct perf_event *event)
{
	box->pmu->type->ops->disable_event(box, event);
}