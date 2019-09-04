#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ base; } ;
struct intel_crt {TYPE_3__ base; } ;
struct i2c_adapter {int dummy; } ;
struct edid {int input; } ;
struct TYPE_4__ {int /*<<< orphan*/  crt_ddc_pin; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 scalar_t__ INTEL_OUTPUT_ANALOG ; 
 struct intel_crt* intel_attached_crt (struct drm_connector*) ; 
 struct edid* intel_crt_get_edid (struct drm_connector*,struct i2c_adapter*) ; 
 struct i2c_adapter* intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_crt_detect_ddc(struct drm_connector *connector)
{
	struct intel_crt *crt = intel_attached_crt(connector);
	struct drm_i915_private *dev_priv = to_i915(crt->base.base.dev);
	struct edid *edid;
	struct i2c_adapter *i2c;
	bool ret = false;

	BUG_ON(crt->base.type != INTEL_OUTPUT_ANALOG);

	i2c = intel_gmbus_get_adapter(dev_priv, dev_priv->vbt.crt_ddc_pin);
	edid = intel_crt_get_edid(connector, i2c);

	if (edid) {
		bool is_digital = edid->input & DRM_EDID_INPUT_DIGITAL;

		/*
		 * This may be a DVI-I connector with a shared DDC
		 * link between analog and digital outputs, so we
		 * have to check the EDID input spec of the attached device.
		 */
		if (!is_digital) {
			DRM_DEBUG_KMS("CRT detected via DDC:0x50 [EDID]\n");
			ret = true;
		} else {
			DRM_DEBUG_KMS("CRT not detected via DDC:0x50 [EDID reports a digital panel]\n");
		}
	} else {
		DRM_DEBUG_KMS("CRT not detected via DDC:0x50 [no valid EDID found]\n");
	}

	kfree(edid);

	return ret;
}