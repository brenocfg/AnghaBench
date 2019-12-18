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
struct insert_mode {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; } ;
struct drm_mm_node {int dummy; } ;
struct drm_mm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_node (struct drm_mm_node*,struct drm_mm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int drm_mm_insert_node_in_range (struct drm_mm*,struct drm_mm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool expect_insert_in_range(struct drm_mm *mm, struct drm_mm_node *node,
				   u64 size, u64 alignment, unsigned long color,
				   u64 range_start, u64 range_end,
				   const struct insert_mode *mode)
{
	int err;

	err = drm_mm_insert_node_in_range(mm, node,
					  size, alignment, color,
					  range_start, range_end,
					  mode->mode);
	if (err) {
		pr_err("insert (size=%llu, alignment=%llu, color=%lu, mode=%s) nto range [%llx, %llx] failed with err=%d\n",
		       size, alignment, color, mode->name,
		       range_start, range_end, err);
		return false;
	}

	if (!assert_node(node, mm, size, alignment, color)) {
		drm_mm_remove_node(node);
		return false;
	}

	return true;
}