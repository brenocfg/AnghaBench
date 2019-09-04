#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  size_t u16 ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct pch_gbe_hw {TYPE_2__* reg; TYPE_3__ mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  ADDR_MASK; TYPE_1__* mac_adr; } ;
struct TYPE_4__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_BUSY ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_mac_mar_set (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_wait_clr_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_gbe_mac_init_rx_addrs(struct pch_gbe_hw *hw, u16 mar_count)
{
	u32 i;

	/* Setup the receive address */
	pch_gbe_mac_mar_set(hw, hw->mac.addr, 0);

	/* Zero out the other receive addresses */
	for (i = 1; i < mar_count; i++) {
		iowrite32(0, &hw->reg->mac_adr[i].high);
		iowrite32(0, &hw->reg->mac_adr[i].low);
	}
	iowrite32(0xFFFE, &hw->reg->ADDR_MASK);
	/* wait busy */
	pch_gbe_wait_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
}