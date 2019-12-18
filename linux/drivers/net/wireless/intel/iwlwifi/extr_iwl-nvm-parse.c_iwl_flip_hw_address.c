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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static void iwl_flip_hw_address(__le32 mac_addr0, __le32 mac_addr1, u8 *dest)
{
	const u8 *hw_addr;

	hw_addr = (const u8 *)&mac_addr0;
	dest[0] = hw_addr[3];
	dest[1] = hw_addr[2];
	dest[2] = hw_addr[1];
	dest[3] = hw_addr[0];

	hw_addr = (const u8 *)&mac_addr1;
	dest[4] = hw_addr[1];
	dest[5] = hw_addr[0];
}