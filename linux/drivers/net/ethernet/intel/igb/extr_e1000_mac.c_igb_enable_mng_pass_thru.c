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
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_FACTPS ; 
 int E1000_FACTPS_MNGCG ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_MODE_MASK ; 
 int E1000_FWSM_MODE_SHIFT ; 
 int /*<<< orphan*/  E1000_MANC ; 
 int E1000_MANC_ASF_EN ; 
 int E1000_MANC_RCV_TCO_EN ; 
 int E1000_MANC_SMBUS_EN ; 
 int e1000_mng_mode_pt ; 
 int rd32 (int /*<<< orphan*/ ) ; 

bool igb_enable_mng_pass_thru(struct e1000_hw *hw)
{
	u32 manc;
	u32 fwsm, factps;
	bool ret_val = false;

	if (!hw->mac.asf_firmware_present)
		goto out;

	manc = rd32(E1000_MANC);

	if (!(manc & E1000_MANC_RCV_TCO_EN))
		goto out;

	if (hw->mac.arc_subsystem_valid) {
		fwsm = rd32(E1000_FWSM);
		factps = rd32(E1000_FACTPS);

		if (!(factps & E1000_FACTPS_MNGCG) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) ==
		     (e1000_mng_mode_pt << E1000_FWSM_MODE_SHIFT))) {
			ret_val = true;
			goto out;
		}
	} else {
		if ((manc & E1000_MANC_SMBUS_EN) &&
		    !(manc & E1000_MANC_ASF_EN)) {
			ret_val = true;
			goto out;
		}
	}

out:
	return ret_val;
}