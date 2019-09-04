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
typedef  int int32_t ;

/* Variables and functions */
 int A6XX_TEX_SAMP_0_LOD_BIAS__MASK ; 
 int A6XX_TEX_SAMP_0_LOD_BIAS__SHIFT ; 

__attribute__((used)) static inline uint32_t A6XX_TEX_SAMP_0_LOD_BIAS(float val)
{
	return ((((int32_t)(val * 256.0))) << A6XX_TEX_SAMP_0_LOD_BIAS__SHIFT) & A6XX_TEX_SAMP_0_LOD_BIAS__MASK;
}