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
struct drm_i915_error_state_buf {int bytes; int size; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 scalar_t__ WARN (int,char*) ; 

__attribute__((used)) static bool __i915_error_ok(struct drm_i915_error_state_buf *e)
{

	if (!e->err && WARN(e->bytes > (e->size - 1), "overflow")) {
		e->err = -ENOSPC;
		return false;
	}

	if (e->bytes == e->size - 1 || e->err)
		return false;

	return true;
}