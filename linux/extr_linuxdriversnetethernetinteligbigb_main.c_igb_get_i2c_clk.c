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
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int E1000_I2C_CLK_IN ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_get_i2c_clk(void *data)
{
	struct igb_adapter *adapter = (struct igb_adapter *)data;
	struct e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	return !!(i2cctl & E1000_I2C_CLK_IN);
}