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
typedef  enum a3xx_color_swap { ____Placeholder_a3xx_color_swap } a3xx_color_swap ;

/* Variables and functions */
 int A5XX_TEX_CONST_0_SWAP__MASK ; 
 int A5XX_TEX_CONST_0_SWAP__SHIFT ; 

__attribute__((used)) static inline uint32_t A5XX_TEX_CONST_0_SWAP(enum a3xx_color_swap val)
{
	return ((val) << A5XX_TEX_CONST_0_SWAP__SHIFT) & A5XX_TEX_CONST_0_SWAP__MASK;
}