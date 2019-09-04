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
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int radeon_debugfs_ring_init(struct radeon_device *rdev, struct radeon_ring *ring)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned i;
	for (i = 0; i < ARRAY_SIZE(radeon_debugfs_ring_info_list); ++i) {
		struct drm_info_list *info = &radeon_debugfs_ring_info_list[i];
		int ridx = *(int*)radeon_debugfs_ring_info_list[i].data;
		unsigned r;

		if (&rdev->ring[ridx] != ring)
			continue;

		r = radeon_debugfs_add_files(rdev, info, 1);
		if (r)
			return r;
	}
#endif
	return 0;
}