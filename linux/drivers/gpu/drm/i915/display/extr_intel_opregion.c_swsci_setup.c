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
struct intel_opregion {int swsci_gbda_sub_functions; int swsci_sbcb_sub_functions; } ;
struct drm_i915_private {struct intel_opregion opregion; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  SWSCI_GBDA_REQUESTED_CALLBACKS ; 
 int /*<<< orphan*/  SWSCI_GBDA_SUPPORTED_CALLS ; 
 int /*<<< orphan*/  SWSCI_SBCB_SUPPORTED_CALLBACKS ; 
 scalar_t__ swsci (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void swsci_setup(struct drm_i915_private *dev_priv)
{
	struct intel_opregion *opregion = &dev_priv->opregion;
	bool requested_callbacks = false;
	u32 tmp;

	/* Sub-function code 0 is okay, let's allow them. */
	opregion->swsci_gbda_sub_functions = 1;
	opregion->swsci_sbcb_sub_functions = 1;

	/* We use GBDA to ask for supported GBDA calls. */
	if (swsci(dev_priv, SWSCI_GBDA_SUPPORTED_CALLS, 0, &tmp) == 0) {
		/* make the bits match the sub-function codes */
		tmp <<= 1;
		opregion->swsci_gbda_sub_functions |= tmp;
	}

	/*
	 * We also use GBDA to ask for _requested_ SBCB callbacks. The driver
	 * must not call interfaces that are not specifically requested by the
	 * bios.
	 */
	if (swsci(dev_priv, SWSCI_GBDA_REQUESTED_CALLBACKS, 0, &tmp) == 0) {
		/* here, the bits already match sub-function codes */
		opregion->swsci_sbcb_sub_functions |= tmp;
		requested_callbacks = true;
	}

	/*
	 * But we use SBCB to ask for _supported_ SBCB calls. This does not mean
	 * the callback is _requested_. But we still can't call interfaces that
	 * are not requested.
	 */
	if (swsci(dev_priv, SWSCI_SBCB_SUPPORTED_CALLBACKS, 0, &tmp) == 0) {
		/* make the bits match the sub-function codes */
		u32 low = tmp & 0x7ff;
		u32 high = tmp & ~0xfff; /* bit 11 is reserved */
		tmp = (high << 4) | (low << 1) | 1;

		/* best guess what to do with supported wrt requested */
		if (requested_callbacks) {
			u32 req = opregion->swsci_sbcb_sub_functions;
			if ((req & tmp) != req)
				DRM_DEBUG_DRIVER("SWSCI BIOS requested (%08x) SBCB callbacks that are not supported (%08x)\n", req, tmp);
			/* XXX: for now, trust the requested callbacks */
			/* opregion->swsci_sbcb_sub_functions &= tmp; */
		} else {
			opregion->swsci_sbcb_sub_functions |= tmp;
		}
	}

	DRM_DEBUG_DRIVER("SWSCI GBDA callbacks %08x, SBCB callbacks %08x\n",
			 opregion->swsci_gbda_sub_functions,
			 opregion->swsci_sbcb_sub_functions);
}