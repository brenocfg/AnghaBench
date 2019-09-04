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
struct ksz_hw {int /*<<< orphan*/ * override_addr; scalar_t__ io; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ KS884X_ADDR_0_OFFSET ; 
 size_t MAC_ADDR_ORDER (int) ; 
 int /*<<< orphan*/  sw_set_addr (struct ksz_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_set_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		writeb(hw->override_addr[MAC_ADDR_ORDER(i)],
			hw->io + KS884X_ADDR_0_OFFSET + i);

	sw_set_addr(hw, hw->override_addr);
}