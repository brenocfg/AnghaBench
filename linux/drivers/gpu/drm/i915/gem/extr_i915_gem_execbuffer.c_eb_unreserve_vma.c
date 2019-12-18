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
struct i915_vma {int dummy; } ;

/* Variables and functions */
 unsigned int __EXEC_OBJECT_HAS_PIN ; 
 unsigned int __EXEC_OBJECT_RESERVED ; 
 int /*<<< orphan*/  __eb_unreserve_vma (struct i915_vma*,unsigned int) ; 

__attribute__((used)) static inline void
eb_unreserve_vma(struct i915_vma *vma, unsigned int *flags)
{
	if (!(*flags & __EXEC_OBJECT_HAS_PIN))
		return;

	__eb_unreserve_vma(vma, *flags);
	*flags &= ~__EXEC_OBJECT_RESERVED;
}