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
struct intel_context {TYPE_1__* ops; scalar_t__ pin_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unpin ) (struct intel_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct intel_context*) ; 

__attribute__((used)) static inline void intel_context_unpin(struct intel_context *ce)
{
	GEM_BUG_ON(!ce->pin_count);
	if (--ce->pin_count)
		return;

	GEM_BUG_ON(!ce->ops);
	ce->ops->unpin(ce);
}