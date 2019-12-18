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
typedef  int /*<<< orphan*/  SVGA3dSurfaceFormat ;

/* Variables and functions */
 int svga3dsurface_is_dx_screen_target_format (int /*<<< orphan*/ ) ; 
 scalar_t__ svga3dsurface_is_gb_screen_target_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
svga3dsurface_is_screen_target_format(SVGA3dSurfaceFormat format)
{
	if (svga3dsurface_is_gb_screen_target_format(format)) {
		return true;
	}
	return svga3dsurface_is_dx_screen_target_format(format);
}