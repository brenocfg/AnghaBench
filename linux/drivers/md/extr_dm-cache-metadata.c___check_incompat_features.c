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
typedef  int uint32_t ;
struct dm_cache_metadata {TYPE_1__* bdev; } ;
struct cache_disk_superblock {int /*<<< orphan*/  compat_ro_flags; int /*<<< orphan*/  incompat_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned long) ; 
 int DM_CACHE_FEATURE_COMPAT_RO_SUPP ; 
 int DM_CACHE_FEATURE_INCOMPAT_SUPP ; 
 int EINVAL ; 
 scalar_t__ get_disk_ro (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __check_incompat_features(struct cache_disk_superblock *disk_super,
				     struct dm_cache_metadata *cmd)
{
	uint32_t incompat_flags, features;

	incompat_flags = le32_to_cpu(disk_super->incompat_flags);
	features = incompat_flags & ~DM_CACHE_FEATURE_INCOMPAT_SUPP;
	if (features) {
		DMERR("could not access metadata due to unsupported optional features (%lx).",
		      (unsigned long)features);
		return -EINVAL;
	}

	/*
	 * Check for read-only metadata to skip the following RDWR checks.
	 */
	if (get_disk_ro(cmd->bdev->bd_disk))
		return 0;

	features = le32_to_cpu(disk_super->compat_ro_flags) & ~DM_CACHE_FEATURE_COMPAT_RO_SUPP;
	if (features) {
		DMERR("could not access metadata RDWR due to unsupported optional features (%lx).",
		      (unsigned long)features);
		return -EINVAL;
	}

	return 0;
}