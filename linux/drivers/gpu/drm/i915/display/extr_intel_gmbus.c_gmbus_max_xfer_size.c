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
 unsigned int GEN9_GMBUS_BYTE_COUNT_MAX ; 
 unsigned int GMBUS_BYTE_COUNT_MAX ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static inline
unsigned int gmbus_max_xfer_size(struct drm_i915_private *dev_priv)
{
	return INTEL_GEN(dev_priv) >= 9 ? GEN9_GMBUS_BYTE_COUNT_MAX :
	       GMBUS_BYTE_COUNT_MAX;
}