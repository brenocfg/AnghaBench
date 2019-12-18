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
 int /*<<< orphan*/  IGC_SWSM ; 
 int IGC_SWSM_SMBI ; 
 int IGC_SWSM_SWESMBI ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

void igc_put_hw_semaphore(struct igc_hw *hw)
{
	u32 swsm;

	swsm = rd32(IGC_SWSM);

	swsm &= ~(IGC_SWSM_SMBI | IGC_SWSM_SWESMBI);

	wr32(IGC_SWSM, swsm);
}