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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_ERR_BLK_PHY_RESET ; 
 int /*<<< orphan*/  IGC_MANC ; 
 int IGC_MANC_BLK_PHY_RST_ON_IDE ; 
 int rd32 (int /*<<< orphan*/ ) ; 

s32 igc_check_reset_block(struct igc_hw *hw)
{
	u32 manc;

	manc = rd32(IGC_MANC);

	return (manc & IGC_MANC_BLK_PHY_RST_ON_IDE) ?
		IGC_ERR_BLK_PHY_RESET : 0;
}