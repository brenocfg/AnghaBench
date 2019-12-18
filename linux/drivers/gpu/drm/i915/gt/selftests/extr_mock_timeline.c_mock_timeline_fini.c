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
struct intel_timeline {int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_syncmap_free (int /*<<< orphan*/ *) ; 

void mock_timeline_fini(struct intel_timeline *timeline)
{
	i915_syncmap_free(&timeline->sync);
}