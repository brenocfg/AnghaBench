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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_priv (struct clk_hw*) ; 
 int /*<<< orphan*/  usb2_clock_sel_enable_extal_only (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb2_clock_sel_enable(struct clk_hw *hw)
{
	usb2_clock_sel_enable_extal_only(to_priv(hw));

	return 0;
}