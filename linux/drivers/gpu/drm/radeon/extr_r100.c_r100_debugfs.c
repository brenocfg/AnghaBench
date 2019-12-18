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
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int r100_debugfs_mc_info_init (struct radeon_device*) ; 

__attribute__((used)) static void r100_debugfs(struct radeon_device *rdev)
{
	int r;

	r = r100_debugfs_mc_info_init(rdev);
	if (r)
		dev_warn(rdev->dev, "Failed to create r100_mc debugfs file.\n");
}