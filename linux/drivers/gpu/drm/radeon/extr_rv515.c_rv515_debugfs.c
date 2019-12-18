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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ r100_debugfs_rbbm_init (struct radeon_device*) ; 
 scalar_t__ rv515_debugfs_ga_info_init (struct radeon_device*) ; 
 scalar_t__ rv515_debugfs_pipes_info_init (struct radeon_device*) ; 

void rv515_debugfs(struct radeon_device *rdev)
{
	if (r100_debugfs_rbbm_init(rdev)) {
		DRM_ERROR("Failed to register debugfs file for RBBM !\n");
	}
	if (rv515_debugfs_pipes_info_init(rdev)) {
		DRM_ERROR("Failed to register debugfs file for pipes !\n");
	}
	if (rv515_debugfs_ga_info_init(rdev)) {
		DRM_ERROR("Failed to register debugfs file for pipes !\n");
	}
}