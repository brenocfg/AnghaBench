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
typedef  int u32 ;

/* Variables and functions */
 int DTD_MAX_WIDTH_SHFT ; 

__attribute__((used)) static inline u32 dtd_max_width_height(int max_width, int max_height)
{
	return (max_width << DTD_MAX_WIDTH_SHFT) | max_height;
}