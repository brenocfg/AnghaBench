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
struct rb_root_cached {int dummy; } ;
struct drm_mm_node {int dummy; } ;
struct drm_mm {int /*<<< orphan*/  head_node; int /*<<< orphan*/  interval_tree; } ;

/* Variables and functions */
 scalar_t__ drm_mm_interval_tree_iter_first (struct rb_root_cached*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct drm_mm_node *
__drm_mm_interval_first(const struct drm_mm *mm, u64 start, u64 last)
{
	return drm_mm_interval_tree_iter_first((struct rb_root_cached *)&mm->interval_tree,
					       start, last) ?: (struct drm_mm_node *)&mm->head_node;
}