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
struct drm_exynos_ipp_limit_val {unsigned int min; unsigned int max; int /*<<< orphan*/  align; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned int,unsigned int,unsigned int) ; 
 int __align_check (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __size_limit_check(unsigned int val,
				 struct drm_exynos_ipp_limit_val *l)
{
	if ((l->min && val < l->min) || (l->max && val > l->max)) {
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (min %d, max %d)\n",
				 val, l->min, l->max);
		return false;
	}
	return __align_check(val, l->align);
}