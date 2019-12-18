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
typedef  enum a5xx_color_fmt { ____Placeholder_a5xx_color_fmt } a5xx_color_fmt ;

/* Variables and functions */
 int A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT__MASK ; 
 int A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT__SHIFT ; 

__attribute__((used)) static inline uint32_t A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT(enum a5xx_color_fmt val)
{
	return ((val) << A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT__SHIFT) & A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT__MASK;
}