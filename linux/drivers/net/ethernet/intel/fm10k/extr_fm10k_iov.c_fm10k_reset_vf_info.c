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
struct fm10k_vf_info {int /*<<< orphan*/  vf_idx; int /*<<< orphan*/  glort; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_lport ) (struct fm10k_hw*,struct fm10k_vf_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* assign_default_mac_vlan ) (struct fm10k_hw*,struct fm10k_vf_info*) ;int /*<<< orphan*/  (* reset_lport ) (struct fm10k_hw*,struct fm10k_vf_info*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ iov; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_VF_FLAG_MULTI_CAPABLE ; 
 int /*<<< orphan*/  fm10k_clear_macvlan_queue (struct fm10k_intfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_vf_info*) ; 
 int /*<<< orphan*/  stub3 (struct fm10k_hw*,struct fm10k_vf_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fm10k_reset_vf_info(struct fm10k_intfc *interface,
				       struct fm10k_vf_info *vf_info)
{
	struct fm10k_hw *hw = &interface->hw;

	/* assigning the MAC address will send a mailbox message */
	fm10k_mbx_lock(interface);

	/* disable LPORT for this VF which clears switch rules */
	hw->iov.ops.reset_lport(hw, vf_info);

	fm10k_clear_macvlan_queue(interface, vf_info->glort, false);

	/* assign new MAC+VLAN for this VF */
	hw->iov.ops.assign_default_mac_vlan(hw, vf_info);

	/* re-enable the LPORT for this VF */
	hw->iov.ops.set_lport(hw, vf_info, vf_info->vf_idx,
			      FM10K_VF_FLAG_MULTI_CAPABLE);

	fm10k_mbx_unlock(interface);
}