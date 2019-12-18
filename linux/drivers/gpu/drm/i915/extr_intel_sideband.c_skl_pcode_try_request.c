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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int __sandybridge_pcode_rw (struct drm_i915_private*,int,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool skl_pcode_try_request(struct drm_i915_private *i915, u32 mbox,
				  u32 request, u32 reply_mask, u32 reply,
				  u32 *status)
{
	*status = __sandybridge_pcode_rw(i915, mbox, &request, NULL,
					 500, 0,
					 true);

	return *status || ((request & reply_mask) == reply);
}