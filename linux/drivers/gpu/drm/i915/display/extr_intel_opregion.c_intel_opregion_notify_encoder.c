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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int type; int port; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DISPLAY_TYPE_CRT ; 
 int DISPLAY_TYPE_EXTERNAL_FLAT_PANEL ; 
 int DISPLAY_TYPE_INTERNAL_FLAT_PANEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
#define  INTEL_OUTPUT_ANALOG 134 
#define  INTEL_OUTPUT_DDI 133 
#define  INTEL_OUTPUT_DP 132 
#define  INTEL_OUTPUT_DP_MST 131 
#define  INTEL_OUTPUT_DSI 130 
#define  INTEL_OUTPUT_EDP 129 
#define  INTEL_OUTPUT_HDMI 128 
 int PORT_E ; 
 int /*<<< orphan*/  SWSCI_SBCB_DISPLAY_POWER_STATE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int swsci (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int intel_opregion_notify_encoder(struct intel_encoder *intel_encoder,
				  bool enable)
{
	struct drm_i915_private *dev_priv = to_i915(intel_encoder->base.dev);
	u32 parm = 0;
	u32 type = 0;
	u32 port;

	/* don't care about old stuff for now */
	if (!HAS_DDI(dev_priv))
		return 0;

	if (intel_encoder->type == INTEL_OUTPUT_DSI)
		port = 0;
	else
		port = intel_encoder->port;

	if (port == PORT_E)  {
		port = 0;
	} else {
		parm |= 1 << port;
		port++;
	}

	if (!enable)
		parm |= 4 << 8;

	switch (intel_encoder->type) {
	case INTEL_OUTPUT_ANALOG:
		type = DISPLAY_TYPE_CRT;
		break;
	case INTEL_OUTPUT_DDI:
	case INTEL_OUTPUT_DP:
	case INTEL_OUTPUT_HDMI:
	case INTEL_OUTPUT_DP_MST:
		type = DISPLAY_TYPE_EXTERNAL_FLAT_PANEL;
		break;
	case INTEL_OUTPUT_EDP:
	case INTEL_OUTPUT_DSI:
		type = DISPLAY_TYPE_INTERNAL_FLAT_PANEL;
		break;
	default:
		WARN_ONCE(1, "unsupported intel_encoder type %d\n",
			  intel_encoder->type);
		return -EINVAL;
	}

	parm |= type << (16 + port * 3);

	return swsci(dev_priv, SWSCI_SBCB_DISPLAY_POWER_STATE, parm, NULL);
}