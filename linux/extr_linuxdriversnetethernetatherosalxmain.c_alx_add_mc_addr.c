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
typedef  int u32 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void alx_add_mc_addr(struct alx_hw *hw, const u8 *addr, u32 *mc_hash)
{
	u32 crc32, bit, reg;

	crc32 = ether_crc(ETH_ALEN, addr);
	reg = (crc32 >> 31) & 0x1;
	bit = (crc32 >> 26) & 0x1F;

	mc_hash[reg] |= BIT(bit);
}