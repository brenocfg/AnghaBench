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
struct ksz_hw {int /*<<< orphan*/ * address; scalar_t__ io; } ;

/* Variables and functions */
 int ADDITIONAL_ENTRIES ; 
 int ADD_ADDR_INCR ; 
 scalar_t__ KS_ADD_ADDR_0_HI ; 
 scalar_t__ empty_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_ena_add_addr (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_set_add_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < ADDITIONAL_ENTRIES; i++) {
		if (empty_addr(hw->address[i]))
			writel(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
		else
			hw_ena_add_addr(hw, i, hw->address[i]);
	}
}