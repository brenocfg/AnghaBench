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
typedef  int uint32_t ;
typedef  enum adreno_compare_func { ____Placeholder_adreno_compare_func } adreno_compare_func ;

/* Variables and functions */
 int A5XX_RB_DEPTH_CNTL_ZFUNC__MASK ; 
 int A5XX_RB_DEPTH_CNTL_ZFUNC__SHIFT ; 

__attribute__((used)) static inline uint32_t A5XX_RB_DEPTH_CNTL_ZFUNC(enum adreno_compare_func val)
{
	return ((val) << A5XX_RB_DEPTH_CNTL_ZFUNC__SHIFT) & A5XX_RB_DEPTH_CNTL_ZFUNC__MASK;
}