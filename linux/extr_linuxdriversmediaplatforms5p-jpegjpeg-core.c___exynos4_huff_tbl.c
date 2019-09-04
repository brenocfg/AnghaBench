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
 int EXYNOS4_HUFF_TBL_HACCL ; 
 int EXYNOS4_HUFF_TBL_HACCV ; 
 int EXYNOS4_HUFF_TBL_HACLL ; 
 int EXYNOS4_HUFF_TBL_HACLV ; 
 int EXYNOS4_HUFF_TBL_HDCCL ; 
 int EXYNOS4_HUFF_TBL_HDCCV ; 
 int EXYNOS4_HUFF_TBL_HDCLL ; 
 int EXYNOS4_HUFF_TBL_HDCLV ; 

__attribute__((used)) static inline int __exynos4_huff_tbl(int class, int id, bool lenval)
{
	/*
	 * class: 0 - DC, 1 - AC
	 * id: 0 - Y, 1 - Cb/Cr
	 */
	if (class) {
		if (id)
			return lenval ? EXYNOS4_HUFF_TBL_HACCL :
				EXYNOS4_HUFF_TBL_HACCV;
		return lenval ? EXYNOS4_HUFF_TBL_HACLL : EXYNOS4_HUFF_TBL_HACLV;

	}
	/* class == 0 */
	if (id)
		return lenval ? EXYNOS4_HUFF_TBL_HDCCL : EXYNOS4_HUFF_TBL_HDCCV;

	return lenval ? EXYNOS4_HUFF_TBL_HDCLL : EXYNOS4_HUFF_TBL_HDCLV;
}