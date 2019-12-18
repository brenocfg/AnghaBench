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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct igc_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_DUPLEX ; 
 int /*<<< orphan*/  HALF_DUPLEX ; 
 int /*<<< orphan*/  IGC_STATUS ; 
 int IGC_STATUS_FD ; 
 int IGC_STATUS_SPEED_100 ; 
 int IGC_STATUS_SPEED_1000 ; 
 int IGC_STATUS_SPEED_2500 ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igc_i225 ; 
 int rd32 (int /*<<< orphan*/ ) ; 

s32 igc_get_speed_and_duplex_copper(struct igc_hw *hw, u16 *speed,
				    u16 *duplex)
{
	u32 status;

	status = rd32(IGC_STATUS);
	if (status & IGC_STATUS_SPEED_1000) {
		/* For I225, STATUS will indicate 1G speed in both 1 Gbps
		 * and 2.5 Gbps link modes. An additional bit is used
		 * to differentiate between 1 Gbps and 2.5 Gbps.
		 */
		if (hw->mac.type == igc_i225 &&
		    (status & IGC_STATUS_SPEED_2500)) {
			*speed = SPEED_2500;
			hw_dbg("2500 Mbs, ");
		} else {
			*speed = SPEED_1000;
			hw_dbg("1000 Mbs, ");
		}
	} else if (status & IGC_STATUS_SPEED_100) {
		*speed = SPEED_100;
		hw_dbg("100 Mbs, ");
	} else {
		*speed = SPEED_10;
		hw_dbg("10 Mbs, ");
	}

	if (status & IGC_STATUS_FD) {
		*duplex = FULL_DUPLEX;
		hw_dbg("Full Duplex\n");
	} else {
		*duplex = HALF_DUPLEX;
		hw_dbg("Half Duplex\n");
	}

	return 0;
}