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
struct ice_hw {struct ice_vsi_ctx** vsi_ctx; } ;

/* Variables and functions */
 size_t ICE_MAX_VSI ; 

struct ice_vsi_ctx *ice_get_vsi_ctx(struct ice_hw *hw, u16 vsi_handle)
{
	return (vsi_handle >= ICE_MAX_VSI) ? NULL : hw->vsi_ctx[vsi_handle];
}