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
typedef  int /*<<< orphan*/  u8 ;
struct ksz_hw {int addr_list_size; scalar_t__ io; int /*<<< orphan*/ * address; } ;

/* Variables and functions */
 int ADD_ADDR_INCR ; 
 scalar_t__ KS_ADD_ADDR_0_HI ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hw_del_addr(struct ksz_hw *hw, u8 *mac_addr)
{
	int i;

	for (i = 0; i < hw->addr_list_size; i++) {
		if (ether_addr_equal(hw->address[i], mac_addr)) {
			eth_zero_addr(hw->address[i]);
			writel(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
			return 0;
		}
	}
	return -1;
}