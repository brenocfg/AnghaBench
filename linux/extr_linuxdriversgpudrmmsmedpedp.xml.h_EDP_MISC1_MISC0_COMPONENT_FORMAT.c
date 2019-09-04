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
typedef  enum edp_component_format { ____Placeholder_edp_component_format } edp_component_format ;

/* Variables and functions */
 int EDP_MISC1_MISC0_COMPONENT_FORMAT__MASK ; 
 int EDP_MISC1_MISC0_COMPONENT_FORMAT__SHIFT ; 

__attribute__((used)) static inline uint32_t EDP_MISC1_MISC0_COMPONENT_FORMAT(enum edp_component_format val)
{
	return ((val) << EDP_MISC1_MISC0_COMPONENT_FORMAT__SHIFT) & EDP_MISC1_MISC0_COMPONENT_FORMAT__MASK;
}