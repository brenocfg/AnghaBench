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
struct ksz_hw {int addr_list_size; int /*<<< orphan*/ * address; int /*<<< orphan*/  override_addr; } ;

/* Variables and functions */
 int ADDITIONAL_ENTRIES ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ empty_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_ena_add_addr (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_add_addr(struct ksz_hw *hw, u8 *mac_addr)
{
	int i;
	int j = ADDITIONAL_ENTRIES;

	if (ether_addr_equal(hw->override_addr, mac_addr))
		return 0;
	for (i = 0; i < hw->addr_list_size; i++) {
		if (ether_addr_equal(hw->address[i], mac_addr))
			return 0;
		if (ADDITIONAL_ENTRIES == j && empty_addr(hw->address[i]))
			j = i;
	}
	if (j < ADDITIONAL_ENTRIES) {
		memcpy(hw->address[j], mac_addr, ETH_ALEN);
		hw_ena_add_addr(hw, j, hw->address[j]);
		return 0;
	}
	return -1;
}