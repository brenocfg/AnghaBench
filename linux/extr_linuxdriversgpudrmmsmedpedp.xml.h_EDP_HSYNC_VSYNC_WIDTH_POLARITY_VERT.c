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
 int EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT__MASK ; 
 int EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT__SHIFT ; 

__attribute__((used)) static inline uint32_t EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT(uint32_t val)
{
	return ((val) << EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT__SHIFT) & EDP_HSYNC_VSYNC_WIDTH_POLARITY_VERT__MASK;
}