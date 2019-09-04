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
typedef  int u16 ;
struct nes_device {scalar_t__ regs; struct nes_adapter* nesadapter; } ;
struct nes_adapter {scalar_t__ hw_rev; int* link_interrupt_count; int port_count; scalar_t__ OneG_Mode; } ;

/* Variables and functions */
 scalar_t__ NE020_REV ; 
 scalar_t__ NES_IDX_ETH_SERDES_COMMON_CONTROL1 ; 
 scalar_t__ NES_IDX_PHY_PCS_CONTROL_STATUS0 ; 
 scalar_t__ NES_MAX_LINK_INTERRUPTS ; 
 scalar_t__ NES_SOFTWARE_RESET ; 
 int /*<<< orphan*/  mh_detected ; 
 int nes_read32 (scalar_t__) ; 
 int nes_read_indexed (struct nes_device*,scalar_t__) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,scalar_t__,int) ; 

__attribute__((used)) static void nes_reset_link(struct nes_device *nesdev, u32 mac_index)
{
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 reset_value;
	u32 i=0;
	u32 u32temp;

	if (nesadapter->hw_rev == NE020_REV) {
		return;
	}
	mh_detected++;

	reset_value = nes_read32(nesdev->regs+NES_SOFTWARE_RESET);

	if ((mac_index == 0) || ((mac_index == 1) && (nesadapter->OneG_Mode)))
		reset_value |= 0x0000001d;
	else
		reset_value |= 0x0000002d;

	if (4 <= (nesadapter->link_interrupt_count[mac_index] / ((u16)NES_MAX_LINK_INTERRUPTS))) {
		if ((!nesadapter->OneG_Mode) && (nesadapter->port_count == 2)) {
			nesadapter->link_interrupt_count[0] = 0;
			nesadapter->link_interrupt_count[1] = 0;
			u32temp = nes_read_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1);
			if (0x00000040 & u32temp)
				nes_write_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1, 0x0000F088);
			else
				nes_write_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1, 0x0000F0C8);

			reset_value |= 0x0000003d;
		}
		nesadapter->link_interrupt_count[mac_index] = 0;
	}

	nes_write32(nesdev->regs+NES_SOFTWARE_RESET, reset_value);

	while (((nes_read32(nesdev->regs+NES_SOFTWARE_RESET)
			& 0x00000040) != 0x00000040) && (i++ < 5000));

	if (0x0000003d == (reset_value & 0x0000003d)) {
		u32 pcs_control_status0, pcs_control_status1;

		for (i = 0; i < 10; i++) {
			pcs_control_status0 = nes_read_indexed(nesdev, NES_IDX_PHY_PCS_CONTROL_STATUS0);
			pcs_control_status1 = nes_read_indexed(nesdev, NES_IDX_PHY_PCS_CONTROL_STATUS0 + 0x200);
			if (((0x0F000000 == (pcs_control_status0 & 0x0F000000))
			     && (pcs_control_status0 & 0x00100000))
			    || ((0x0F000000 == (pcs_control_status1 & 0x0F000000))
				&& (pcs_control_status1 & 0x00100000)))
				continue;
			else
				break;
		}
		if (10 == i) {
			u32temp = nes_read_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1);
			if (0x00000040 & u32temp)
				nes_write_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1, 0x0000F088);
			else
				nes_write_indexed(nesdev, NES_IDX_ETH_SERDES_COMMON_CONTROL1, 0x0000F0C8);

			nes_write32(nesdev->regs+NES_SOFTWARE_RESET, reset_value);

			while (((nes_read32(nesdev->regs + NES_SOFTWARE_RESET)
				 & 0x00000040) != 0x00000040) && (i++ < 5000));
		}
	}
}