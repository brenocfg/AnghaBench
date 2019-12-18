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
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ MAX_PLOAD_CREDIT ; 
 scalar_t__ payload_credits_available (struct drm_i915_private*,int) ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void wait_for_payload_credits(struct drm_i915_private *dev_priv,
				     enum transcoder dsi_trans)
{
	if (wait_for_us(payload_credits_available(dev_priv, dsi_trans) >=
			MAX_PLOAD_CREDIT, 100))
		DRM_ERROR("DSI payload credits not released\n");
}