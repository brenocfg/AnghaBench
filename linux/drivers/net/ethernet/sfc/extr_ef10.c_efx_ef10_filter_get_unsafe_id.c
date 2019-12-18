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
 int EFX_EF10_FILTER_ID_INVALID ; 
 int HUNT_FILTER_TBL_ROWS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static u32 efx_ef10_filter_get_unsafe_id(u32 filter_id)
{
	WARN_ON_ONCE(filter_id == EFX_EF10_FILTER_ID_INVALID);
	return filter_id & (HUNT_FILTER_TBL_ROWS - 1);
}