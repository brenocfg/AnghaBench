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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  e1000_82573 128 
 scalar_t__ e1000_get_hw_semaphore_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_put_hw_semaphore_82571 (struct e1000_hw*) ; 
 scalar_t__ e1000e_acquire_nvm (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_acquire_nvm_82571(struct e1000_hw *hw)
{
	s32 ret_val;

	ret_val = e1000_get_hw_semaphore_82571(hw);
	if (ret_val)
		return ret_val;

	switch (hw->mac.type) {
	case e1000_82573:
		break;
	default:
		ret_val = e1000e_acquire_nvm(hw);
		break;
	}

	if (ret_val)
		e1000_put_hw_semaphore_82571(hw);

	return ret_val;
}