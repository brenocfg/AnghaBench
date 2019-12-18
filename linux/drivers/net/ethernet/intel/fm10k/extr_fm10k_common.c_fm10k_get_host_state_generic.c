#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* process ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;} ;
struct fm10k_mbx_info {scalar_t__ state; int /*<<< orphan*/  timeout; TYPE_1__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* request_lport_map ) (struct fm10k_hw*) ;} ;
struct fm10k_mac_info {int get_host_state; scalar_t__ dglort_map; TYPE_2__ ops; scalar_t__ tx_ready; } ;
struct fm10k_hw {struct fm10k_mac_info mac; struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  FM10K_ERR_RESET_REQUESTED ; 
 scalar_t__ FM10K_STATE_OPEN ; 
 int /*<<< orphan*/  FM10K_TXDCTL (int /*<<< orphan*/ ) ; 
 int FM10K_TXDCTL_ENABLE ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*) ; 

s32 fm10k_get_host_state_generic(struct fm10k_hw *hw, bool *host_ready)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	struct fm10k_mac_info *mac = &hw->mac;
	s32 ret_val = 0;
	u32 txdctl = fm10k_read_reg(hw, FM10K_TXDCTL(0));

	/* process upstream mailbox in case interrupts were disabled */
	mbx->ops.process(hw, mbx);

	/* If Tx is no longer enabled link should come down */
	if (!(~txdctl) || !(txdctl & FM10K_TXDCTL_ENABLE))
		mac->get_host_state = true;

	/* exit if not checking for link, or link cannot be changed */
	if (!mac->get_host_state || !(~txdctl))
		goto out;

	/* if we somehow dropped the Tx enable we should reset */
	if (mac->tx_ready && !(txdctl & FM10K_TXDCTL_ENABLE)) {
		ret_val = FM10K_ERR_RESET_REQUESTED;
		goto out;
	}

	/* if Mailbox timed out we should request reset */
	if (!mbx->timeout) {
		ret_val = FM10K_ERR_RESET_REQUESTED;
		goto out;
	}

	/* verify Mailbox is still open */
	if (mbx->state != FM10K_STATE_OPEN)
		goto out;

	/* interface cannot receive traffic without logical ports */
	if (mac->dglort_map == FM10K_DGLORTMAP_NONE) {
		if (mac->ops.request_lport_map)
			ret_val = mac->ops.request_lport_map(hw);

		goto out;
	}

	/* if we passed all the tests above then the switch is ready and we no
	 * longer need to check for link
	 */
	mac->get_host_state = false;

out:
	*host_ready = !mac->get_host_state;
	return ret_val;
}