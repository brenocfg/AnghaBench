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
struct drm_mode_fb_cmd2 {int* modifier; int /*<<< orphan*/  pixel_format; } ;
struct drm_format_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  I915_FORMAT_MOD_Y_TILED_CCS 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 int /*<<< orphan*/  ccs_formats ; 
 struct drm_format_info const* lookup_format_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct drm_format_info *
intel_get_format_info(const struct drm_mode_fb_cmd2 *cmd)
{
	switch (cmd->modifier[0]) {
	case I915_FORMAT_MOD_Y_TILED_CCS:
	case I915_FORMAT_MOD_Yf_TILED_CCS:
		return lookup_format_info(ccs_formats,
					  ARRAY_SIZE(ccs_formats),
					  cmd->pixel_format);
	default:
		return NULL;
	}
}