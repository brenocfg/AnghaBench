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

/* Variables and functions */
 int QOS_L3_MBM_TOTAL_EVENT_ID ; 
 int rdt_mon_features ; 

__attribute__((used)) static inline bool is_mbm_total_enabled(void)
{
	return (rdt_mon_features & (1 << QOS_L3_MBM_TOTAL_EVENT_ID));
}