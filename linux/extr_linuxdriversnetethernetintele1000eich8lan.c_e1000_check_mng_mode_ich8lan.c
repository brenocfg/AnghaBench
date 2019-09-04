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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int E1000_FWSM_MODE_MASK ; 
 int E1000_FWSM_MODE_SHIFT ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int E1000_ICH_MNG_IAMT_MODE ; 
 int /*<<< orphan*/  FWSM ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool e1000_check_mng_mode_ich8lan(struct e1000_hw *hw)
{
	u32 fwsm;

	fwsm = er32(FWSM);
	return (fwsm & E1000_ICH_FWSM_FW_VALID) &&
		((fwsm & E1000_FWSM_MODE_MASK) ==
		 (E1000_ICH_MNG_IAMT_MODE << E1000_FWSM_MODE_SHIFT));
}