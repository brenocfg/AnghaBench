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
typedef  enum a3xx_tex_type { ____Placeholder_a3xx_tex_type } a3xx_tex_type ;

/* Variables and functions */
 int A3XX_TEX_CONST_0_TYPE__MASK ; 
 int A3XX_TEX_CONST_0_TYPE__SHIFT ; 

__attribute__((used)) static inline uint32_t A3XX_TEX_CONST_0_TYPE(enum a3xx_tex_type val)
{
	return ((val) << A3XX_TEX_CONST_0_TYPE__SHIFT) & A3XX_TEX_CONST_0_TYPE__MASK;
}