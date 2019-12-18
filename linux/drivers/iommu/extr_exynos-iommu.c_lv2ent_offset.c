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
typedef  int sysmmu_iova_t ;

/* Variables and functions */
 int NUM_LV2ENTRIES ; 
 int SPAGE_ORDER ; 

__attribute__((used)) static u32 lv2ent_offset(sysmmu_iova_t iova)
{
	return (iova >> SPAGE_ORDER) & (NUM_LV2ENTRIES - 1);
}