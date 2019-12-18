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
struct ksz_hw {scalar_t__ id; int /*<<< orphan*/ * override_addr; int /*<<< orphan*/ * perm_addr; int /*<<< orphan*/  mac_override; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DEFAULT_MAC_ADDRESS ; 
 int ETH_ALEN ; 
 scalar_t__ KS884X_ADDR_0_OFFSET ; 
 size_t MAC_ADDR_ORDER (int) ; 
 scalar_t__ empty_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_set_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static void hw_read_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		hw->perm_addr[MAC_ADDR_ORDER(i)] = readb(hw->io +
			KS884X_ADDR_0_OFFSET + i);

	if (!hw->mac_override) {
		memcpy(hw->override_addr, hw->perm_addr, ETH_ALEN);
		if (empty_addr(hw->override_addr)) {
			memcpy(hw->perm_addr, DEFAULT_MAC_ADDRESS, ETH_ALEN);
			memcpy(hw->override_addr, DEFAULT_MAC_ADDRESS,
			       ETH_ALEN);
			hw->override_addr[5] += hw->id;
			hw_set_addr(hw);
		}
	}
}