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
typedef  int /*<<< orphan*/  u8 ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  y420_vdb_modes; } ;
struct drm_display_info {TYPE_1__ hdmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_match_cea_mode (struct drm_display_mode const*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool drm_mode_is_420_only(const struct drm_display_info *display,
			  const struct drm_display_mode *mode)
{
	u8 vic = drm_match_cea_mode(mode);

	return test_bit(vic, display->hdmi.y420_vdb_modes);
}