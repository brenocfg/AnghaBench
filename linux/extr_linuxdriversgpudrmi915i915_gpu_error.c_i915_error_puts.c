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
struct drm_i915_error_state_buf {scalar_t__ pos; scalar_t__ start; unsigned int size; unsigned int bytes; int buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_error_advance (struct drm_i915_error_state_buf*,unsigned int) ; 
 int /*<<< orphan*/  __i915_error_ok (struct drm_i915_error_state_buf*) ; 
 int /*<<< orphan*/  __i915_error_seek (struct drm_i915_error_state_buf*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static void i915_error_puts(struct drm_i915_error_state_buf *e,
			    const char *str)
{
	unsigned len;

	if (!__i915_error_ok(e))
		return;

	len = strlen(str);

	/* Seek the first printf which is hits start position */
	if (e->pos < e->start) {
		if (!__i915_error_seek(e, len))
			return;
	}

	if (len >= e->size - e->bytes)
		len = e->size - e->bytes - 1;
	memcpy(e->buf + e->bytes, str, len);

	__i915_error_advance(e, len);
}