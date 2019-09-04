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

__attribute__((used)) static u32 e1000_get_phy_addr_for_bm_page(u32 page, u32 reg)
{
	u32 phy_addr = 2;

	if ((page >= 768) || (page == 0 && reg == 25) || (reg == 31))
		phy_addr = 1;

	return phy_addr;
}