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
typedef  int /*<<< orphan*/  u64 ;
struct drm_mm_node {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct drm_mm {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int drm_mm_insert_node_in_range (struct drm_mm*,struct drm_mm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool expect_insert_in_range_fail(struct drm_mm *mm,
					u64 size,
					u64 range_start,
					u64 range_end)
{
	struct drm_mm_node tmp = {};
	int err;

	err = drm_mm_insert_node_in_range(mm, &tmp,
					  size, 0, 0,
					  range_start, range_end,
					  0);
	if (likely(err == -ENOSPC))
		return true;

	if (!err) {
		pr_err("impossible insert succeeded, node %llx + %llu, range [%llx, %llx]\n",
		       tmp.start, tmp.size, range_start, range_end);
		drm_mm_remove_node(&tmp);
	} else {
		pr_err("impossible insert failed with wrong error %d [expected %d], size %llu, range [%llx, %llx]\n",
		       err, -ENOSPC, size, range_start, range_end);
	}

	return false;
}