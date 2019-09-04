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
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline bool __align_check(unsigned int val, unsigned int align)
{
	if (align && (val & (align - 1))) {
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (align %d)\n",
				 val, align);
		return false;
	}
	return true;
}