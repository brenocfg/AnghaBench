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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_BLK_PHY_RESET ; 
 int E1000_ICH_FWSM_RSPCIPHY ; 
 int /*<<< orphan*/  FWSM ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_check_reset_block_ich8lan(struct e1000_hw *hw)
{
	bool blocked = false;
	int i = 0;

	while ((blocked = !(er32(FWSM) & E1000_ICH_FWSM_RSPCIPHY)) &&
	       (i++ < 30))
		usleep_range(10000, 11000);
	return blocked ? E1000_BLK_PHY_RESET : 0;
}