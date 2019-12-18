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
typedef  size_t u16 ;
struct ice_hw {TYPE_3__* blk; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_5__ {TYPE_1__* vsis; } ;
struct TYPE_6__ {TYPE_2__ xlt2; } ;
struct TYPE_4__ {size_t vsig; } ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 size_t ICE_MAX_VSI ; 

__attribute__((used)) static enum ice_status
ice_vsig_find_vsi(struct ice_hw *hw, enum ice_block blk, u16 vsi, u16 *vsig)
{
	if (!vsig || vsi >= ICE_MAX_VSI)
		return ICE_ERR_PARAM;

	/* As long as there's a default or valid VSIG associated with the input
	 * VSI, the functions returns a success. Any handling of VSIG will be
	 * done by the following add, update or remove functions.
	 */
	*vsig = hw->blk[blk].xlt2.vsis[vsi].vsig;

	return 0;
}