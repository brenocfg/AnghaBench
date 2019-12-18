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
typedef  int u32 ;
struct atl2_hw {int dummy; } ;

/* Variables and functions */
 int ATL2_READ_REG_ARRAY (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG_ARRAY (struct atl2_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_RX_HASH_TABLE ; 

__attribute__((used)) static void atl2_hash_set(struct atl2_hw *hw, u32 hash_value)
{
	u32 hash_bit, hash_reg;
	u32 mta;

	/* The HASH Table  is a register array of 2 32-bit registers.
	 * It is treated like an array of 64 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what register
	 * the bit is in, read it, OR in the new bit, then write
	 * back the new value.  The register is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * register are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 31) & 0x1;
	hash_bit = (hash_value >> 26) & 0x1F;

	mta = ATL2_READ_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg);

	mta |= (1 << hash_bit);

	ATL2_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg, mta);
}