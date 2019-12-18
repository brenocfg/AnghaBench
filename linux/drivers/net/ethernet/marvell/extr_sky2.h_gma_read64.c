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
typedef  int u64 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 unsigned int SK_GMAC_REG (unsigned int,unsigned int) ; 
 scalar_t__ sky2_read16 (struct sky2_hw*,unsigned int) ; 

__attribute__((used)) static inline u64 gma_read64(struct sky2_hw *hw, unsigned port, unsigned reg)
{
	unsigned base = SK_GMAC_REG(port, reg);

	return (u64) sky2_read16(hw, base)
		| (u64) sky2_read16(hw, base+4) << 16
		| (u64) sky2_read16(hw, base+8) << 32
		| (u64) sky2_read16(hw, base+12) << 48;
}