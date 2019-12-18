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
 int HUNT_FILTER_TBL_ROWS ; 

__attribute__((used)) static unsigned int efx_ef10_filter_get_unsafe_pri(u32 filter_id)
{
	return filter_id / (HUNT_FILTER_TBL_ROWS * 2);
}