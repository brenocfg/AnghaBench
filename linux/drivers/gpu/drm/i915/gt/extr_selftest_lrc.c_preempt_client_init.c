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
struct preempt_client {int /*<<< orphan*/  ctx; int /*<<< orphan*/  spin; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ igt_spinner_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_context (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kernel_context_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int preempt_client_init(struct drm_i915_private *i915,
			       struct preempt_client *c)
{
	c->ctx = kernel_context(i915);
	if (!c->ctx)
		return -ENOMEM;

	if (igt_spinner_init(&c->spin, &i915->gt))
		goto err_ctx;

	return 0;

err_ctx:
	kernel_context_close(c->ctx);
	return -ENOMEM;
}