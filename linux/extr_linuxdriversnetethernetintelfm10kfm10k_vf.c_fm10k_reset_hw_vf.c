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
struct TYPE_2__ {int /*<<< orphan*/  reset_while_pending; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_ERR_REQUESTS_PENDING ; 
 scalar_t__ FM10K_ERR_RESET_FAILED ; 
 int /*<<< orphan*/  FM10K_RESET_TIMEOUT ; 
 int /*<<< orphan*/  FM10K_VFCTRL ; 
 int FM10K_VFCTRL_RST ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_stop_hw_vf (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_write_flush (struct fm10k_hw*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_reset_hw_vf(struct fm10k_hw *hw)
{
	s32 err;

	/* shut down queues we own and reset DMA configuration */
	err = fm10k_stop_hw_vf(hw);
	if (err == FM10K_ERR_REQUESTS_PENDING)
		hw->mac.reset_while_pending++;
	else if (err)
		return err;

	/* Inititate VF reset */
	fm10k_write_reg(hw, FM10K_VFCTRL, FM10K_VFCTRL_RST);

	/* Flush write and allow 100us for reset to complete */
	fm10k_write_flush(hw);
	udelay(FM10K_RESET_TIMEOUT);

	/* Clear reset bit and verify it was cleared */
	fm10k_write_reg(hw, FM10K_VFCTRL, 0);
	if (fm10k_read_reg(hw, FM10K_VFCTRL) & FM10K_VFCTRL_RST)
		return FM10K_ERR_RESET_FAILED;

	return 0;
}