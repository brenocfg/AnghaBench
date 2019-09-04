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

/* Variables and functions */
 scalar_t__ unlikely (unsigned long) ; 

bool i915_memcpy_from_wc(void *dst, const void *src, unsigned long len)
{
	if (unlikely(((unsigned long)dst | (unsigned long)src | len) & 15))
		return false;

#ifdef CONFIG_AS_MOVNTDQA
	if (static_branch_likely(&has_movntdqa)) {
		if (likely(len))
			__memcpy_ntdqa(dst, src, len);
		return true;
	}
#endif

	return false;
}