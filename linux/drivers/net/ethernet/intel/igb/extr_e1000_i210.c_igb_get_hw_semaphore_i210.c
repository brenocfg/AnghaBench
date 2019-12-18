#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int clear_semaphore_once; } ;
struct TYPE_6__ {TYPE_2__ _82575; } ;
struct TYPE_4__ {scalar_t__ word_size; } ;
struct e1000_hw {TYPE_3__ dev_spec; TYPE_1__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_NVM ; 
 int /*<<< orphan*/  E1000_SWSM ; 
 int E1000_SWSM_SMBI ; 
 int E1000_SWSM_SWESMBI ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igb_put_hw_semaphore (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_get_hw_semaphore_i210(struct e1000_hw *hw)
{
	u32 swsm;
	s32 timeout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* Get the SW semaphore */
	while (i < timeout) {
		swsm = rd32(E1000_SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			break;

		udelay(50);
		i++;
	}

	if (i == timeout) {
		/* In rare circumstances, the SW semaphore may already be held
		 * unintentionally. Clear the semaphore once before giving up.
		 */
		if (hw->dev_spec._82575.clear_semaphore_once) {
			hw->dev_spec._82575.clear_semaphore_once = false;
			igb_put_hw_semaphore(hw);
			for (i = 0; i < timeout; i++) {
				swsm = rd32(E1000_SWSM);
				if (!(swsm & E1000_SWSM_SMBI))
					break;

				udelay(50);
			}
		}

		/* If we do not have the semaphore here, we have to give up. */
		if (i == timeout) {
			hw_dbg("Driver can't access device - SMBI bit is set.\n");
			return -E1000_ERR_NVM;
		}
	}

	/* Get the FW semaphore. */
	for (i = 0; i < timeout; i++) {
		swsm = rd32(E1000_SWSM);
		wr32(E1000_SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired if bit latched */
		if (rd32(E1000_SWSM) & E1000_SWSM_SWESMBI)
			break;

		udelay(50);
	}

	if (i == timeout) {
		/* Release semaphores */
		igb_put_hw_semaphore(hw);
		hw_dbg("Driver can't access the NVM\n");
		return -E1000_ERR_NVM;
	}

	return 0;
}