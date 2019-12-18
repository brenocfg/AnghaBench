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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ipu_soc {int dummy; } ;
struct drm_format_info {int num_planes; } ;

/* Variables and functions */
#define  DRM_FORMAT_MOD_LINEAR 130 
#define  DRM_FORMAT_MOD_VIVANTE_SUPER_TILED 129 
#define  DRM_FORMAT_MOD_VIVANTE_TILED 128 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 

bool ipu_prg_format_supported(struct ipu_soc *ipu, uint32_t format,
			      uint64_t modifier)
{
	const struct drm_format_info *info = drm_format_info(format);

	if (info->num_planes != 1)
		return false;

	switch (modifier) {
	case DRM_FORMAT_MOD_LINEAR:
	case DRM_FORMAT_MOD_VIVANTE_TILED:
	case DRM_FORMAT_MOD_VIVANTE_SUPER_TILED:
		return true;
	default:
		return false;
	}
}