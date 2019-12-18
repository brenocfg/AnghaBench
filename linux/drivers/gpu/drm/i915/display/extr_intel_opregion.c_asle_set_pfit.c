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
 int /*<<< orphan*/  ASLC_PFIT_FAILED ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 

__attribute__((used)) static u32 asle_set_pfit(struct drm_i915_private *dev_priv, u32 pfit)
{
	/* Panel fitting is currently controlled by the X code, so this is a
	   noop until modesetting support works fully */
	DRM_DEBUG_DRIVER("Pfit is not supported\n");
	return ASLC_PFIT_FAILED;
}