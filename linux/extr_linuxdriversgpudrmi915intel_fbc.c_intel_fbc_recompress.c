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
 int /*<<< orphan*/  FBC_REND_NUKE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_FBC_REND_STATE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_fbc_recompress(struct drm_i915_private *dev_priv)
{
	I915_WRITE(MSG_FBC_REND_STATE, FBC_REND_NUKE);
	POSTING_READ(MSG_FBC_REND_STATE);
}