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
struct ksz_hw {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_stop_rx (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_stop_tx (struct ksz_hw*) ; 

__attribute__((used)) static void hw_disable(struct ksz_hw *hw)
{
	hw_stop_rx(hw);
	hw_stop_tx(hw);
	hw->enabled = 0;
}