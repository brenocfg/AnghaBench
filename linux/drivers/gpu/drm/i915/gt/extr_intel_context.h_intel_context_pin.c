#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_context {int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */
 int __intel_context_do_pin (struct intel_context*) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int intel_context_pin(struct intel_context *ce)
{
	if (likely(atomic_inc_not_zero(&ce->pin_count)))
		return 0;

	return __intel_context_do_pin(ce);
}