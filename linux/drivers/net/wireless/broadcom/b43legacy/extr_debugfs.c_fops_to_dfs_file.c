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
struct b43legacy_wldev {void* dfsentry; } ;
typedef  void b43legacy_dfs_file ;
struct b43legacy_debugfs_fops {int /*<<< orphan*/  file_struct_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct b43legacy_dfs_file * fops_to_dfs_file(struct b43legacy_wldev *dev,
				       const struct b43legacy_debugfs_fops *dfops)
{
	void *p;

	p = dev->dfsentry;
	p += dfops->file_struct_offset;

	return p;
}