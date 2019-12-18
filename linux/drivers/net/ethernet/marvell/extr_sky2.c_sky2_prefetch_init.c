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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PREF_UNIT_ADDR_HI ; 
 int /*<<< orphan*/  PREF_UNIT_ADDR_LO ; 
 int /*<<< orphan*/  PREF_UNIT_CTRL ; 
 int /*<<< orphan*/  PREF_UNIT_LAST_IDX ; 
 int /*<<< orphan*/  PREF_UNIT_OP_ON ; 
 int /*<<< orphan*/  PREF_UNIT_RST_CLR ; 
 int /*<<< orphan*/  PREF_UNIT_RST_SET ; 
 int /*<<< orphan*/  Y2_QADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_prefetch_init(struct sky2_hw *hw, u32 qaddr,
			       dma_addr_t addr, u32 last)
{
	sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_SET);
	sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_CLR);
	sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_HI), upper_32_bits(addr));
	sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_LO), lower_32_bits(addr));
	sky2_write16(hw, Y2_QADDR(qaddr, PREF_UNIT_LAST_IDX), last);
	sky2_write32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_OP_ON);

	sky2_read32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL));
}