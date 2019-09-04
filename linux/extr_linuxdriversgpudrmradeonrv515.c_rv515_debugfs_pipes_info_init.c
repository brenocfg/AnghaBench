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

__attribute__((used)) static int rv515_debugfs_pipes_info_init(struct radeon_device *rdev)
{
#if defined(CONFIG_DEBUG_FS)
	return radeon_debugfs_add_files(rdev, rv515_pipes_info_list, 1);
#else
	return 0;
#endif
}