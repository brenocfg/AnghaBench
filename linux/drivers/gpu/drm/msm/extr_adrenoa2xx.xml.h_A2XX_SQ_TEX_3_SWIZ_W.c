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
typedef  enum sq_tex_swiz { ____Placeholder_sq_tex_swiz } sq_tex_swiz ;

/* Variables and functions */
 int A2XX_SQ_TEX_3_SWIZ_W__MASK ; 
 int A2XX_SQ_TEX_3_SWIZ_W__SHIFT ; 

__attribute__((used)) static inline uint32_t A2XX_SQ_TEX_3_SWIZ_W(enum sq_tex_swiz val)
{
	return ((val) << A2XX_SQ_TEX_3_SWIZ_W__SHIFT) & A2XX_SQ_TEX_3_SWIZ_W__MASK;
}