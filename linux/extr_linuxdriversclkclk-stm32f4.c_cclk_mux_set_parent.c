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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* set_parent ) (struct clk_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ clk_mux_ops ; 
 int /*<<< orphan*/  disable_power_domain_write_protection () ; 
 int /*<<< orphan*/  enable_power_domain_write_protection () ; 
 int /*<<< orphan*/  sofware_reset_backup_domain () ; 
 int stub1 (struct clk_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cclk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	int ret;

	disable_power_domain_write_protection();

	sofware_reset_backup_domain();

	ret = clk_mux_ops.set_parent(hw, index);

	enable_power_domain_write_protection();

	return ret;
}