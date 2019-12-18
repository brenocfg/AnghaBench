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
struct i915_page_directory {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GFP_ALLOW_FAIL ; 
 struct i915_page_directory* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_page_directory *__alloc_pd(size_t sz)
{
	struct i915_page_directory *pd;

	pd = kzalloc(sz, I915_GFP_ALLOW_FAIL);
	if (unlikely(!pd))
		return NULL;

	spin_lock_init(&pd->lock);
	return pd;
}