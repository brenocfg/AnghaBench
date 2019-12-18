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
struct drm_i915_error_state_buf {scalar_t__ bytes; scalar_t__ size; scalar_t__ buf; scalar_t__ err; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  __i915_error_grow (struct drm_i915_error_state_buf*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static void i915_error_puts(struct drm_i915_error_state_buf *e, const char *str)
{
	unsigned len;

	if (e->err || !str)
		return;

	len = strlen(str);
	if (!__i915_error_grow(e, len))
		return;

	GEM_BUG_ON(e->bytes + len > e->size);
	memcpy(e->buf + e->bytes, str, len);
	e->bytes += len;
}