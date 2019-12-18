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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct ice_vsi_ctx {size_t* num_lan_q_entries; struct ice_q_ctx** lan_q_ctx; } ;
struct ice_q_ctx {int dummy; } ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 struct ice_vsi_ctx* ice_get_vsi_ctx (struct ice_hw*,size_t) ; 

__attribute__((used)) static struct ice_q_ctx *
ice_get_lan_q_ctx(struct ice_hw *hw, u16 vsi_handle, u8 tc, u16 q_handle)
{
	struct ice_vsi_ctx *vsi;
	struct ice_q_ctx *q_ctx;

	vsi = ice_get_vsi_ctx(hw, vsi_handle);
	if (!vsi)
		return NULL;
	if (q_handle >= vsi->num_lan_q_entries[tc])
		return NULL;
	if (!vsi->lan_q_ctx[tc])
		return NULL;
	q_ctx = vsi->lan_q_ctx[tc];
	return &q_ctx[q_handle];
}