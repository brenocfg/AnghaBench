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
typedef  enum adreno_rb_blend_factor { ____Placeholder_adreno_rb_blend_factor } adreno_rb_blend_factor ;

/* Variables and functions */
 int A6XX_RB_MRT_BLEND_CONTROL_ALPHA_DEST_FACTOR__MASK ; 
 int A6XX_RB_MRT_BLEND_CONTROL_ALPHA_DEST_FACTOR__SHIFT ; 

__attribute__((used)) static inline uint32_t A6XX_RB_MRT_BLEND_CONTROL_ALPHA_DEST_FACTOR(enum adreno_rb_blend_factor val)
{
	return ((val) << A6XX_RB_MRT_BLEND_CONTROL_ALPHA_DEST_FACTOR__SHIFT) & A6XX_RB_MRT_BLEND_CONTROL_ALPHA_DEST_FACTOR__MASK;
}