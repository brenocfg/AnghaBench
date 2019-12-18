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
typedef  scalar_t__ SVGA3dSurfaceFormat ;

/* Variables and functions */
 scalar_t__ SVGA3D_B8G8R8A8_UNORM ; 
 scalar_t__ SVGA3D_B8G8R8X8_UNORM ; 
 scalar_t__ SVGA3D_R8G8B8A8_UNORM ; 

__attribute__((used)) static inline bool
svga3dsurface_is_dx_screen_target_format(SVGA3dSurfaceFormat format)
{
	return (format == SVGA3D_R8G8B8A8_UNORM ||
		format == SVGA3D_B8G8R8A8_UNORM ||
		format == SVGA3D_B8G8R8X8_UNORM);
}