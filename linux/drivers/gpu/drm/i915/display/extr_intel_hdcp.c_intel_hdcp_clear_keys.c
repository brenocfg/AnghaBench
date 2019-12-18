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
 int HDCP_CLEAR_KEYS_TRIGGER ; 
 int HDCP_FUSE_DONE ; 
 int HDCP_FUSE_ERROR ; 
 int HDCP_FUSE_IN_PROGRESS ; 
 int /*<<< orphan*/  HDCP_KEY_CONF ; 
 int HDCP_KEY_LOAD_DONE ; 
 int HDCP_KEY_LOAD_STATUS ; 
 int /*<<< orphan*/  HDCP_KEY_STATUS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_hdcp_clear_keys(struct drm_i915_private *dev_priv)
{
	I915_WRITE(HDCP_KEY_CONF, HDCP_CLEAR_KEYS_TRIGGER);
	I915_WRITE(HDCP_KEY_STATUS, HDCP_KEY_LOAD_DONE | HDCP_KEY_LOAD_STATUS |
		   HDCP_FUSE_IN_PROGRESS | HDCP_FUSE_ERROR | HDCP_FUSE_DONE);
}