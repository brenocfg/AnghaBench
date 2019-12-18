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
struct work_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ epoch; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  epoch ; 
 int /*<<< orphan*/  i915_globals_shrink () ; 
 TYPE_1__ park ; 

__attribute__((used)) static void __i915_globals_park(struct work_struct *work)
{
	/* Confirm nothing woke up in the last grace period */
	if (park.epoch == atomic_read(&epoch))
		i915_globals_shrink();
}