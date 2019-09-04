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
 int sandybridge_pcode_read (struct drm_i915_private*,int,int*) ; 

__attribute__((used)) static bool skl_pcode_try_request(struct drm_i915_private *dev_priv, u32 mbox,
				  u32 request, u32 reply_mask, u32 reply,
				  u32 *status)
{
	u32 val = request;

	*status = sandybridge_pcode_read(dev_priv, mbox, &val);

	return *status || ((val & reply_mask) == reply);
}