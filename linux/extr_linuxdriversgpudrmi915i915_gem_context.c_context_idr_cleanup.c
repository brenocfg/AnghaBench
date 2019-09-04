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
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_close (struct i915_gem_context*) ; 

__attribute__((used)) static int context_idr_cleanup(int id, void *p, void *data)
{
	struct i915_gem_context *ctx = p;

	context_close(ctx);
	return 0;
}