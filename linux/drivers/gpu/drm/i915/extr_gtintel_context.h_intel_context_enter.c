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
struct intel_context {TYPE_2__* ops; int /*<<< orphan*/  active_count; TYPE_1__* timeline; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enter ) (struct intel_context*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_context*) ; 

__attribute__((used)) static inline void intel_context_enter(struct intel_context *ce)
{
	lockdep_assert_held(&ce->timeline->mutex);
	if (!ce->active_count++)
		ce->ops->enter(ce);
}