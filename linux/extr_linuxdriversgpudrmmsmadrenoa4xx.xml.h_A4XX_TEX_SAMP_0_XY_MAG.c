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
typedef  enum a4xx_tex_filter { ____Placeholder_a4xx_tex_filter } a4xx_tex_filter ;

/* Variables and functions */
 int A4XX_TEX_SAMP_0_XY_MAG__MASK ; 
 int A4XX_TEX_SAMP_0_XY_MAG__SHIFT ; 

__attribute__((used)) static inline uint32_t A4XX_TEX_SAMP_0_XY_MAG(enum a4xx_tex_filter val)
{
	return ((val) << A4XX_TEX_SAMP_0_XY_MAG__SHIFT) & A4XX_TEX_SAMP_0_XY_MAG__MASK;
}