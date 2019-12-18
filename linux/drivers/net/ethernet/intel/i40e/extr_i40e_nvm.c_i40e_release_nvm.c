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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ asq_cmd_timeout; } ;
struct TYPE_3__ {scalar_t__ blank_nvm_mode; } ;
struct i40e_hw {TYPE_2__ aq; TYPE_1__ nvm; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_ERR_ADMIN_QUEUE_TIMEOUT ; 
 int /*<<< orphan*/  I40E_NVM_RESOURCE_ID ; 
 scalar_t__ I40E_SUCCESS ; 
 scalar_t__ i40e_aq_release_resource (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void i40e_release_nvm(struct i40e_hw *hw)
{
	i40e_status ret_code = I40E_SUCCESS;
	u32 total_delay = 0;

	if (hw->nvm.blank_nvm_mode)
		return;

	ret_code = i40e_aq_release_resource(hw, I40E_NVM_RESOURCE_ID, 0, NULL);

	/* there are some rare cases when trying to release the resource
	 * results in an admin Q timeout, so handle them correctly
	 */
	while ((ret_code == I40E_ERR_ADMIN_QUEUE_TIMEOUT) &&
	       (total_delay < hw->aq.asq_cmd_timeout)) {
		usleep_range(1000, 2000);
		ret_code = i40e_aq_release_resource(hw,
						    I40E_NVM_RESOURCE_ID,
						    0, NULL);
		total_delay++;
	}
}