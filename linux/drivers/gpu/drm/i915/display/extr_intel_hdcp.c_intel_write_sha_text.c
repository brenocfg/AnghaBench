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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HDCP_REP_CTL ; 
 int /*<<< orphan*/  HDCP_SHA1_READY ; 
 int /*<<< orphan*/  HDCP_SHA_TEXT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_write_sha_text(struct drm_i915_private *dev_priv, u32 sha_text)
{
	I915_WRITE(HDCP_SHA_TEXT, sha_text);
	if (intel_de_wait_for_set(dev_priv, HDCP_REP_CTL, HDCP_SHA1_READY, 1)) {
		DRM_ERROR("Timed out waiting for SHA1 ready\n");
		return -ETIMEDOUT;
	}
	return 0;
}