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
struct intel_reset {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WEDGED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __intel_reset_failed(const struct intel_reset *reset)
{
	return unlikely(test_bit(I915_WEDGED, &reset->flags));
}