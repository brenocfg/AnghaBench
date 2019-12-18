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
typedef  int u8 ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static bool hpx3_cap_ver_matches(u8 pcie_cap_id, u8 hpx3_cap_id)
{
	u8 cap_ver = hpx3_cap_id & 0xf;

	if ((hpx3_cap_id & BIT(4)) && cap_ver >= pcie_cap_id)
		return true;
	else if (cap_ver == pcie_cap_id)
		return true;

	return false;
}