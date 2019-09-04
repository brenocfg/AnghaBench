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
 scalar_t__ SVGA3D_A1R5G5B5 ; 
 scalar_t__ SVGA3D_A8R8G8B8 ; 
 scalar_t__ SVGA3D_P8 ; 
 scalar_t__ SVGA3D_R5G6B5 ; 
 scalar_t__ SVGA3D_X1R5G5B5 ; 
 scalar_t__ SVGA3D_X8R8G8B8 ; 

__attribute__((used)) static inline bool
svga3dsurface_is_gb_screen_target_format(SVGA3dSurfaceFormat format)
{
	return (format == SVGA3D_X8R8G8B8 ||
		format == SVGA3D_A8R8G8B8 ||
		format == SVGA3D_R5G6B5   ||
		format == SVGA3D_X1R5G5B5 ||
		format == SVGA3D_A1R5G5B5 ||
		format == SVGA3D_P8);
}