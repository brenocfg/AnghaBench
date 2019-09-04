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

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_TLBCOMMAND ; 
 int /*<<< orphan*/  ARC_REG_TLBPD0 ; 
 int /*<<< orphan*/  ARC_REG_TLBPD1 ; 
 int /*<<< orphan*/  ARC_REG_TLBPD1HI ; 
 int /*<<< orphan*/  TLBWrite ; 
 scalar_t__ is_pae40_enabled () ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __tlb_entry_erase(void)
{
	write_aux_reg(ARC_REG_TLBPD1, 0);

	if (is_pae40_enabled())
		write_aux_reg(ARC_REG_TLBPD1HI, 0);

	write_aux_reg(ARC_REG_TLBPD0, 0);
	write_aux_reg(ARC_REG_TLBCOMMAND, TLBWrite);
}