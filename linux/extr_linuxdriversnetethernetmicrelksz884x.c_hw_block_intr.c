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
typedef  int /*<<< orphan*/  uint ;
struct ksz_hw {int /*<<< orphan*/  intr_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_dis_intr (struct ksz_hw*) ; 

__attribute__((used)) static uint hw_block_intr(struct ksz_hw *hw)
{
	uint interrupt = 0;

	if (!hw->intr_blocked) {
		hw_dis_intr(hw);
		interrupt = hw->intr_blocked;
	}
	return interrupt;
}