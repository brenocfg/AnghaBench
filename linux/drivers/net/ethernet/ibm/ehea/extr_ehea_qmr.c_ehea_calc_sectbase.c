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
 int EHEA_DIR_INDEX_SHIFT ; 
 int EHEA_TOP_INDEX_SHIFT ; 
 unsigned long SECTION_SIZE_BITS ; 
 void* __va (unsigned long) ; 

__attribute__((used)) static inline void *ehea_calc_sectbase(int top, int dir, int idx)
{
	unsigned long ret = idx;
	ret |= dir << EHEA_DIR_INDEX_SHIFT;
	ret |= top << EHEA_TOP_INDEX_SHIFT;
	return __va(ret << SECTION_SIZE_BITS);
}