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
 int EDP_START_HOR_VER_FROM_SYNC_HORIZ__MASK ; 
 int EDP_START_HOR_VER_FROM_SYNC_HORIZ__SHIFT ; 

__attribute__((used)) static inline uint32_t EDP_START_HOR_VER_FROM_SYNC_HORIZ(uint32_t val)
{
	return ((val) << EDP_START_HOR_VER_FROM_SYNC_HORIZ__SHIFT) & EDP_START_HOR_VER_FROM_SYNC_HORIZ__MASK;
}