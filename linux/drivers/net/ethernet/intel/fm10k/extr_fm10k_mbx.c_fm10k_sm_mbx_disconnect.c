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
struct TYPE_2__ {int /*<<< orphan*/  (* process ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;} ;
struct fm10k_mbx_info {int timeout; scalar_t__ state; int /*<<< orphan*/  mbmem_reg; int /*<<< orphan*/  tx; scalar_t__ remote; TYPE_1__ ops; int /*<<< orphan*/  mbx_reg; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int FM10K_MBX_DISCONNECT_TIMEOUT ; 
 int FM10K_MBX_INTERRUPT_DISABLE ; 
 scalar_t__ FM10K_MBX_POLL_DELAY ; 
 int FM10K_MBX_REQ ; 
 scalar_t__ FM10K_STATE_CLOSED ; 
 scalar_t__ FM10K_STATE_DISCONNECT ; 
 int /*<<< orphan*/  fm10k_fifo_drop_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm10k_mbx_reset_work (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void fm10k_sm_mbx_disconnect(struct fm10k_hw *hw,
				    struct fm10k_mbx_info *mbx)
{
	int timeout = mbx->timeout ? FM10K_MBX_DISCONNECT_TIMEOUT : 0;

	/* Place mbx in ready to disconnect state */
	mbx->state = FM10K_STATE_DISCONNECT;

	/* trigger interrupt to start shutdown process */
	fm10k_write_reg(hw, mbx->mbx_reg, FM10K_MBX_REQ |
					  FM10K_MBX_INTERRUPT_DISABLE);
	do {
		udelay(FM10K_MBX_POLL_DELAY);
		mbx->ops.process(hw, mbx);
		timeout -= FM10K_MBX_POLL_DELAY;
	} while ((timeout > 0) && (mbx->state != FM10K_STATE_CLOSED));

	/* in case we didn't close just force the mailbox into shutdown */
	mbx->state = FM10K_STATE_CLOSED;
	mbx->remote = 0;
	fm10k_mbx_reset_work(mbx);
	fm10k_fifo_drop_all(&mbx->tx);

	fm10k_write_reg(hw, mbx->mbmem_reg, 0);
}