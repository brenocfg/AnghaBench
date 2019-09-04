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
struct TYPE_3__ {scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ asq; } ;
struct i40e_hw {TYPE_2__ aq; } ;

/* Variables and functions */
 int I40E_PF_ATQLEN_ATQENABLE_MASK ; 
 int rd32 (struct i40e_hw*,scalar_t__) ; 

bool i40e_check_asq_alive(struct i40e_hw *hw)
{
	if (hw->aq.asq.len)
		return !!(rd32(hw, hw->aq.asq.len) &
			  I40E_PF_ATQLEN_ATQENABLE_MASK);
	else
		return false;
}