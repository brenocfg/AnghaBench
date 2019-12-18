#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int need_pll_quirk; } ;

/* Variables and functions */
 TYPE_1__ amd_chipset ; 
 int /*<<< orphan*/  usb_amd_find_chipset_info () ; 

bool usb_amd_quirk_pll_check(void)
{
	usb_amd_find_chipset_info();
	return amd_chipset.need_pll_quirk;
}