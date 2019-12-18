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
struct igc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_EECD ; 
 int IGC_EECD_FLASH_DETECTED_I225 ; 
 int rd32 (int /*<<< orphan*/ ) ; 

bool igc_get_flash_presence_i225(struct igc_hw *hw)
{
	bool ret_val = false;
	u32 eec = 0;

	eec = rd32(IGC_EECD);
	if (eec & IGC_EECD_FLASH_DETECTED_I225)
		ret_val = true;

	return ret_val;
}