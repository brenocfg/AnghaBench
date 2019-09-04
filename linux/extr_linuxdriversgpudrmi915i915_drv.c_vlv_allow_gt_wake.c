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
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_GTLC_ALLOWWAKEACK ; 
 int /*<<< orphan*/  VLV_GTLC_ALLOWWAKEREQ ; 
 int /*<<< orphan*/  VLV_GTLC_WAKE_CTRL ; 
 int vlv_wait_for_pw_status (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlv_allow_gt_wake(struct drm_i915_private *dev_priv, bool allow)
{
	u32 mask;
	u32 val;
	int err;

	val = I915_READ(VLV_GTLC_WAKE_CTRL);
	val &= ~VLV_GTLC_ALLOWWAKEREQ;
	if (allow)
		val |= VLV_GTLC_ALLOWWAKEREQ;
	I915_WRITE(VLV_GTLC_WAKE_CTRL, val);
	POSTING_READ(VLV_GTLC_WAKE_CTRL);

	mask = VLV_GTLC_ALLOWWAKEACK;
	val = allow ? mask : 0;

	err = vlv_wait_for_pw_status(dev_priv, mask, val);
	if (err)
		DRM_ERROR("timeout disabling GT waking\n");

	return err;
}