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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ arc_subsystem_valid; int /*<<< orphan*/  asf_firmware_present; } ;
struct igc_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_FACTPS ; 
 int IGC_FACTPS_MNGCG ; 
 int /*<<< orphan*/  IGC_FWSM ; 
 int IGC_FWSM_MODE_MASK ; 
 int IGC_FWSM_MODE_SHIFT ; 
 int /*<<< orphan*/  IGC_MANC ; 
 int IGC_MANC_ASF_EN ; 
 int IGC_MANC_RCV_TCO_EN ; 
 int IGC_MANC_SMBUS_EN ; 
 int igc_mng_mode_pt ; 
 int rd32 (int /*<<< orphan*/ ) ; 

bool igc_enable_mng_pass_thru(struct igc_hw *hw)
{
	bool ret_val = false;
	u32 fwsm, factps;
	u32 manc;

	if (!hw->mac.asf_firmware_present)
		goto out;

	manc = rd32(IGC_MANC);

	if (!(manc & IGC_MANC_RCV_TCO_EN))
		goto out;

	if (hw->mac.arc_subsystem_valid) {
		fwsm = rd32(IGC_FWSM);
		factps = rd32(IGC_FACTPS);

		if (!(factps & IGC_FACTPS_MNGCG) &&
		    ((fwsm & IGC_FWSM_MODE_MASK) ==
		    (igc_mng_mode_pt << IGC_FWSM_MODE_SHIFT))) {
			ret_val = true;
			goto out;
		}
	} else {
		if ((manc & IGC_MANC_SMBUS_EN) &&
		    !(manc & IGC_MANC_ASF_EN)) {
			ret_val = true;
			goto out;
		}
	}

out:
	return ret_val;
}