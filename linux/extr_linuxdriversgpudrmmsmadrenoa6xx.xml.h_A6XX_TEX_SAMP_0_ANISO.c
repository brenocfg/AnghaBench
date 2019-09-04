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
typedef  enum a6xx_tex_aniso { ____Placeholder_a6xx_tex_aniso } a6xx_tex_aniso ;

/* Variables and functions */
 int A6XX_TEX_SAMP_0_ANISO__MASK ; 
 int A6XX_TEX_SAMP_0_ANISO__SHIFT ; 

__attribute__((used)) static inline uint32_t A6XX_TEX_SAMP_0_ANISO(enum a6xx_tex_aniso val)
{
	return ((val) << A6XX_TEX_SAMP_0_ANISO__SHIFT) & A6XX_TEX_SAMP_0_ANISO__MASK;
}