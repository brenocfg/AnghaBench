#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ va; } ;
struct i40e_hw {TYPE_1__ nvm_buff; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_queue_shutdown (struct i40e_hw*,int) ; 
 scalar_t__ i40e_check_asq_alive (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  i40e_shutdown_arq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_shutdown_asq (struct i40e_hw*) ; 

i40e_status i40e_shutdown_adminq(struct i40e_hw *hw)
{
	i40e_status ret_code = 0;

	if (i40e_check_asq_alive(hw))
		i40e_aq_queue_shutdown(hw, true);

	i40e_shutdown_asq(hw);
	i40e_shutdown_arq(hw);

	if (hw->nvm_buff.va)
		i40e_free_virt_mem(hw, &hw->nvm_buff);

	return ret_code;
}