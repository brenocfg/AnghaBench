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
typedef  enum a5xx_tex_clamp { ____Placeholder_a5xx_tex_clamp } a5xx_tex_clamp ;

/* Variables and functions */
 int A5XX_TEX_SAMP_0_WRAP_R__MASK ; 
 int A5XX_TEX_SAMP_0_WRAP_R__SHIFT ; 

__attribute__((used)) static inline uint32_t A5XX_TEX_SAMP_0_WRAP_R(enum a5xx_tex_clamp val)
{
	return ((val) << A5XX_TEX_SAMP_0_WRAP_R__SHIFT) & A5XX_TEX_SAMP_0_WRAP_R__MASK;
}