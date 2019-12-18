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
struct TYPE_2__ {int mock; } ;

/* Variables and functions */
 int ENOTTY ; 
 TYPE_1__ i915_selftest ; 
 int /*<<< orphan*/  mock ; 
 int run_selftests (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i915_mock_selftests(void)
{
	int err;

	if (!i915_selftest.mock)
		return 0;

	err = run_selftests(mock, NULL);
	if (err) {
		i915_selftest.mock = err;
		return err;
	}

	if (i915_selftest.mock < 0) {
		i915_selftest.mock = -ENOTTY;
		return 1;
	}

	return 0;
}