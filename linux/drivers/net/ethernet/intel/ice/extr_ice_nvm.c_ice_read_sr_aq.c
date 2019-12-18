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
typedef  int u32 ;
typedef  int u16 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_aq_read_nvm (struct ice_hw*,int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ *) ; 
 int ice_check_sr_access_params (struct ice_hw*,int,int) ; 

__attribute__((used)) static enum ice_status
ice_read_sr_aq(struct ice_hw *hw, u32 offset, u16 words, u16 *data,
	       bool last_command)
{
	enum ice_status status;

	status = ice_check_sr_access_params(hw, offset, words);

	/* values in "offset" and "words" parameters are sized as words
	 * (16 bits) but ice_aq_read_nvm expects these values in bytes.
	 * So do this conversion while calling ice_aq_read_nvm.
	 */
	if (!status)
		status = ice_aq_read_nvm(hw, 0, 2 * offset, 2 * words, data,
					 last_command, NULL);

	return status;
}