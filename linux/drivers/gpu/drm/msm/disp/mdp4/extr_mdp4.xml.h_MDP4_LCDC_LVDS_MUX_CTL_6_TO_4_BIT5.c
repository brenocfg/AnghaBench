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

/* Variables and functions */
 int MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5__MASK ; 
 int MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(uint32_t val)
{
	return ((val) << MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5__SHIFT) & MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5__MASK;
}