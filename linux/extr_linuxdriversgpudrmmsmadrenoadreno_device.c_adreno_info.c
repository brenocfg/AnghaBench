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
struct adreno_rev {int /*<<< orphan*/  patchid; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  patchid; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  core; } ;
struct adreno_info {TYPE_1__ rev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct adreno_info*) ; 
 scalar_t__ _rev_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adreno_info* gpulist ; 

const struct adreno_info *adreno_info(struct adreno_rev rev)
{
	int i;

	/* identify gpu: */
	for (i = 0; i < ARRAY_SIZE(gpulist); i++) {
		const struct adreno_info *info = &gpulist[i];
		if (_rev_match(info->rev.core, rev.core) &&
				_rev_match(info->rev.major, rev.major) &&
				_rev_match(info->rev.minor, rev.minor) &&
				_rev_match(info->rev.patchid, rev.patchid))
			return info;
	}

	return NULL;
}