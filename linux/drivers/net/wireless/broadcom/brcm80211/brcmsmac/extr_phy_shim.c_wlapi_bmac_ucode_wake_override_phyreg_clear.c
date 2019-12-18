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
struct phy_shim_info {int /*<<< orphan*/  wlc_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_WAKE_OVERRIDE_PHYREG ; 
 int /*<<< orphan*/  brcms_c_ucode_wake_override_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wlapi_bmac_ucode_wake_override_phyreg_clear(struct phy_shim_info *physhim)
{
	brcms_c_ucode_wake_override_clear(physhim->wlc_hw,
					  BRCMS_WAKE_OVERRIDE_PHYREG);
}