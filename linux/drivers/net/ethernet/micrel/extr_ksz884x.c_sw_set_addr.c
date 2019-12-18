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
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS8842_MAC_ADDR_0_OFFSET ; 
 scalar_t__ KS8842_MAC_ADDR_1_OFFSET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sw_set_addr(struct ksz_hw *hw, u8 *mac_addr)
{
	int i;

	for (i = 0; i < 6; i += 2) {
		writeb(mac_addr[i], hw->io + KS8842_MAC_ADDR_0_OFFSET + i);
		writeb(mac_addr[1 + i], hw->io + KS8842_MAC_ADDR_1_OFFSET + i);
	}
}