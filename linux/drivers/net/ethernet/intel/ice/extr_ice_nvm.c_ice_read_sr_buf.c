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
typedef  int /*<<< orphan*/  u16 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_RES_READ ; 
 int ice_acquire_nvm (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int ice_read_sr_buf_aq (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_release_nvm (struct ice_hw*) ; 

enum ice_status
ice_read_sr_buf(struct ice_hw *hw, u16 offset, u16 *words, u16 *data)
{
	enum ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (!status) {
		status = ice_read_sr_buf_aq(hw, offset, words, data);
		ice_release_nvm(hw);
	}

	return status;
}