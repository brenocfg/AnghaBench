#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int rev; scalar_t__ gen; } ;
struct TYPE_4__ {TYPE_1__ sb_type; } ;

/* Variables and functions */
 scalar_t__ AMD_CHIPSET_SB600 ; 
 scalar_t__ AMD_CHIPSET_SB700 ; 
 TYPE_2__ amd_chipset ; 
 int /*<<< orphan*/  usb_amd_find_chipset_info () ; 

bool usb_amd_hang_symptom_quirk(void)
{
	u8 rev;

	usb_amd_find_chipset_info();
	rev = amd_chipset.sb_type.rev;
	/* SB600 and old version of SB700 have hang symptom bug */
	return amd_chipset.sb_type.gen == AMD_CHIPSET_SB600 ||
			(amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			 rev >= 0x3a && rev <= 0x3b);
}