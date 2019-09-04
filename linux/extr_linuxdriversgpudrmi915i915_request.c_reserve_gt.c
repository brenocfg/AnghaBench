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
struct TYPE_2__ {scalar_t__ request_serial; int /*<<< orphan*/  active_requests; } ;
struct drm_i915_private {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_unpark (struct drm_i915_private*) ; 
 int reset_all_global_seqno (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int reserve_gt(struct drm_i915_private *i915)
{
	int ret;

	/*
	 * Reservation is fine until we may need to wrap around
	 *
	 * By incrementing the serial for every request, we know that no
	 * individual engine may exceed that serial (as each is reset to 0
	 * on any wrap). This protects even the most pessimistic of migrations
	 * of every request from all engines onto just one.
	 */
	while (unlikely(++i915->gt.request_serial == 0)) {
		ret = reset_all_global_seqno(i915, 0);
		if (ret) {
			i915->gt.request_serial--;
			return ret;
		}
	}

	if (!i915->gt.active_requests++)
		i915_gem_unpark(i915);

	return 0;
}