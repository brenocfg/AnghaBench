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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int api_maj_ver; int api_min_ver; scalar_t__ asq_last_status; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_2__ aq; TYPE_1__ mac; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_AQ_RC_EAGAIN ; 
 scalar_t__ I40E_MAC_X722 ; 
 scalar_t__ i40evf_aq_rx_ctl_read_register (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

u32 i40evf_read_rx_ctl(struct i40e_hw *hw, u32 reg_addr)
{
	i40e_status status = 0;
	bool use_register;
	int retry = 5;
	u32 val = 0;

	use_register = (((hw->aq.api_maj_ver == 1) &&
			(hw->aq.api_min_ver < 5)) ||
			(hw->mac.type == I40E_MAC_X722));
	if (!use_register) {
do_retry:
		status = i40evf_aq_rx_ctl_read_register(hw, reg_addr,
							&val, NULL);
		if (hw->aq.asq_last_status == I40E_AQ_RC_EAGAIN && retry) {
			usleep_range(1000, 2000);
			retry--;
			goto do_retry;
		}
	}

	/* if the AQ access failed, try the old-fashioned way */
	if (status || use_register)
		val = rd32(hw, reg_addr);

	return val;
}