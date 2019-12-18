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
struct fm10k_hw {int /*<<< orphan*/  hw_addr; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ FM10K_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_write_flush (struct fm10k_hw*) ; 

__attribute__((used)) static int fm10k_hw_ready(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;

	fm10k_write_flush(hw);

	return FM10K_REMOVED(hw->hw_addr) ? -ENODEV : 0;
}