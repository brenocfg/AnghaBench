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
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ idle_work; int /*<<< orphan*/  active_requests; } ;
struct drm_i915_private {TYPE_2__ gt; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
new_requests_since_last_retire(const struct drm_i915_private *i915)
{
	return (READ_ONCE(i915->gt.active_requests) ||
		work_pending(&i915->gt.idle_work.work));
}