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
typedef  enum edp_color_depth { ____Placeholder_edp_color_depth } edp_color_depth ;

/* Variables and functions */
 int EDP_CONFIGURATION_CTRL_COLOR__MASK ; 
 int EDP_CONFIGURATION_CTRL_COLOR__SHIFT ; 

__attribute__((used)) static inline uint32_t EDP_CONFIGURATION_CTRL_COLOR(enum edp_color_depth val)
{
	return ((val) << EDP_CONFIGURATION_CTRL_COLOR__SHIFT) & EDP_CONFIGURATION_CTRL_COLOR__MASK;
}