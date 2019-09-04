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
struct i915_syncmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  i915_syncmap_free (struct i915_syncmap**) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int check_syncmap_free(struct i915_syncmap **sync)
{
	i915_syncmap_free(sync);
	if (*sync) {
		pr_err("sync not cleared after free\n");
		return -EINVAL;
	}

	return 0;
}