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
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_CTL_Q_ADMIN ; 
 int /*<<< orphan*/  ICE_CTL_Q_MAILBOX ; 
 int ice_init_check_adminq (struct ice_hw*) ; 
 int ice_init_ctrlq (struct ice_hw*,int /*<<< orphan*/ ) ; 

enum ice_status ice_init_all_ctrlq(struct ice_hw *hw)
{
	enum ice_status ret_code;

	/* Init FW admin queue */
	ret_code = ice_init_ctrlq(hw, ICE_CTL_Q_ADMIN);
	if (ret_code)
		return ret_code;

	ret_code = ice_init_check_adminq(hw);
	if (ret_code)
		return ret_code;

	/* Init Mailbox queue */
	return ice_init_ctrlq(hw, ICE_CTL_Q_MAILBOX);
}