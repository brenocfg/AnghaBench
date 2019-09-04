#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int mta_reg_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  E1000_MTA ; 
 int array_rd32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrfl () ; 

void igb_mta_set(struct e1000_hw *hw, u32 hash_value)
{
	u32 hash_bit, hash_reg, mta;

	/* The MTA is a register array of 32-bit registers. It is
	 * treated like an array of (32*mta_reg_count) bits.  We want to
	 * set bit BitArray[hash_value]. So we figure out what register
	 * the bit is in, read it, OR in the new bit, then write
	 * back the new value.  The (hw->mac.mta_reg_count - 1) serves as a
	 * mask to bits 31:5 of the hash value which gives us the
	 * register we're modifying.  The hash bit within that register
	 * is determined by the lower 5 bits of the hash value.
	 */
	hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
	hash_bit = hash_value & 0x1F;

	mta = array_rd32(E1000_MTA, hash_reg);

	mta |= BIT(hash_bit);

	array_wr32(E1000_MTA, hash_reg, mta);
	wrfl();
}