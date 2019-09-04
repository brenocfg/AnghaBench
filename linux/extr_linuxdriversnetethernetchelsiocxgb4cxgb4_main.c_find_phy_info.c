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
struct info_10gbt_phy_fw {int phy_fw_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct info_10gbt_phy_fw*) ; 
 struct info_10gbt_phy_fw* phy_info_array ; 

__attribute__((used)) static struct info_10gbt_phy_fw *find_phy_info(int devid)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(phy_info_array); i++) {
		if (phy_info_array[i].phy_fw_id == devid)
			return &phy_info_array[i];
	}
	return NULL;
}