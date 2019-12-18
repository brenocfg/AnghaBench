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
struct drm_format_info {int /*<<< orphan*/  vsub; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fb_plane_height(int height,
			   const struct drm_format_info *format, int plane)
{
	if (plane == 0)
		return height;

	return DIV_ROUND_UP(height, format->vsub);
}