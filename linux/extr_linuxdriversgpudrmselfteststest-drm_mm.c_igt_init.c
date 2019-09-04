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
typedef  int /*<<< orphan*/  tmp ;
struct drm_mm_node {unsigned int size; scalar_t__ start; } ;
struct drm_mm {unsigned int size; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  mm ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert_no_holes (struct drm_mm_node*) ; 
 int /*<<< orphan*/  assert_one_hole (struct drm_mm_node*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  drm_mm_clean (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_init (struct drm_mm_node*,int /*<<< orphan*/ ,unsigned int const) ; 
 scalar_t__ drm_mm_initialized (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int drm_mm_reserve_node (struct drm_mm_node*,struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_takedown (struct drm_mm_node*) ; 
 int /*<<< orphan*/  memset (struct drm_mm_node*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  show_mm (struct drm_mm_node*) ; 

__attribute__((used)) static int igt_init(void *ignored)
{
	const unsigned int size = 4096;
	struct drm_mm mm;
	struct drm_mm_node tmp;
	int ret = -EINVAL;

	/* Start with some simple checks on initialising the struct drm_mm */
	memset(&mm, 0, sizeof(mm));
	if (drm_mm_initialized(&mm)) {
		pr_err("zeroed mm claims to be initialized\n");
		return ret;
	}

	memset(&mm, 0xff, sizeof(mm));
	drm_mm_init(&mm, 0, size);
	if (!drm_mm_initialized(&mm)) {
		pr_err("mm claims not to be initialized\n");
		goto out;
	}

	if (!drm_mm_clean(&mm)) {
		pr_err("mm not empty on creation\n");
		goto out;
	}

	/* After creation, it should all be one massive hole */
	if (!assert_one_hole(&mm, 0, size)) {
		ret = -EINVAL;
		goto out;
	}

	memset(&tmp, 0, sizeof(tmp));
	tmp.start = 0;
	tmp.size = size;
	ret = drm_mm_reserve_node(&mm, &tmp);
	if (ret) {
		pr_err("failed to reserve whole drm_mm\n");
		goto out;
	}

	/* After filling the range entirely, there should be no holes */
	if (!assert_no_holes(&mm)) {
		ret = -EINVAL;
		goto out;
	}

	/* And then after emptying it again, the massive hole should be back */
	drm_mm_remove_node(&tmp);
	if (!assert_one_hole(&mm, 0, size)) {
		ret = -EINVAL;
		goto out;
	}

out:
	if (ret)
		show_mm(&mm);
	drm_mm_takedown(&mm);
	return ret;
}