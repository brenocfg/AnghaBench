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
typedef  size_t u16 ;
struct ice_vsi_ctx {int dummy; } ;
struct ice_hw {int /*<<< orphan*/ ** vsi_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_vsi_ctx*) ; 
 int /*<<< orphan*/  ice_clear_vsi_q_ctx (struct ice_hw*,size_t) ; 
 struct ice_vsi_ctx* ice_get_vsi_ctx (struct ice_hw*,size_t) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static void ice_clear_vsi_ctx(struct ice_hw *hw, u16 vsi_handle)
{
	struct ice_vsi_ctx *vsi;

	vsi = ice_get_vsi_ctx(hw, vsi_handle);
	if (vsi) {
		ice_clear_vsi_q_ctx(hw, vsi_handle);
		devm_kfree(ice_hw_to_dev(hw), vsi);
		hw->vsi_ctx[vsi_handle] = NULL;
	}
}