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
struct drm_i915_private {int dummy; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DSPARB ; 
 int DSPARB_BEND_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PLANE_B ; 
 int /*<<< orphan*/  plane_name (int) ; 

__attribute__((used)) static int i830_get_fifo_size(struct drm_i915_private *dev_priv,
			      enum i9xx_plane_id i9xx_plane)
{
	u32 dsparb = I915_READ(DSPARB);
	int size;

	size = dsparb & 0x1ff;
	if (i9xx_plane == PLANE_B)
		size = ((dsparb >> DSPARB_BEND_SHIFT) & 0x1ff) - size;
	size >>= 1; /* Convert to cachelines */

	DRM_DEBUG_KMS("FIFO size - (0x%08x) %c: %d\n",
		      dsparb, plane_name(i9xx_plane), size);

	return size;
}