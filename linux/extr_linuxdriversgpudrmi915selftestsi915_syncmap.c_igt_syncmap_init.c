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
 int check_syncmap_free (struct i915_syncmap**) ; 
 int /*<<< orphan*/  i915_syncmap_init (struct i915_syncmap**) ; 

__attribute__((used)) static int igt_syncmap_init(void *arg)
{
	struct i915_syncmap *sync = (void *)~0ul;

	/*
	 * Cursory check that we can initialise a random pointer and transform
	 * it into the root pointer of a syncmap.
	 */

	i915_syncmap_init(&sync);
	return check_syncmap_free(&sync);
}