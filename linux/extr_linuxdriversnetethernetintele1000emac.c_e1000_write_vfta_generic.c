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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VFTA ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1e_flush () ; 

void e1000_write_vfta_generic(struct e1000_hw *hw, u32 offset, u32 value)
{
	E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, value);
	e1e_flush();
}