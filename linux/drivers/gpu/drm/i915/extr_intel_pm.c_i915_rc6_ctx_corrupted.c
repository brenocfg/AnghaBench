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

/* Variables and functions */
 int /*<<< orphan*/  GEN8_RC6_CTX_INFO ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i915_rc6_ctx_corrupted(struct drm_i915_private *dev_priv)
{
	return !I915_READ(GEN8_RC6_CTX_INFO);
}