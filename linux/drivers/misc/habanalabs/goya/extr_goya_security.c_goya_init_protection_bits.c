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
typedef  int u8 ;
typedef  int u32 ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int PROT_BITS_OFFS ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  goya_init_dma_protection_bits (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_mme_protection_bits (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_tpc_protection_bits (struct hl_device*) ; 
 int /*<<< orphan*/  goya_pb_set_block (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmPCIE_AUX_BASE ; 
 int /*<<< orphan*/  mmPCIE_CORE_BASE ; 
 int /*<<< orphan*/  mmPCIE_DB_CFG_BASE ; 
 int /*<<< orphan*/  mmPCIE_DB_CMD_BASE ; 
 int /*<<< orphan*/  mmPCIE_DB_RSV_BASE ; 
 int /*<<< orphan*/  mmPCIE_PHY_BASE ; 
 int /*<<< orphan*/  mmPCIE_WRAP_BASE ; 
 int /*<<< orphan*/  mmPCI_NRTR_BASE ; 
 int /*<<< orphan*/  mmPCI_RD_REGULATOR_BASE ; 
 int /*<<< orphan*/  mmPCI_WR_REGULATOR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y0_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y1_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y2_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y3_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y4_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X0_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X0_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X1_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X1_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X2_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X2_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X3_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X3_RTR_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X4_BANK_BASE ; 
 int /*<<< orphan*/  mmSRAM_Y5_X4_RTR_BASE ; 
 int /*<<< orphan*/  mmTPC0_NRTR_BASE ; 
 int /*<<< orphan*/  mmTPC_PLL_BASE ; 
 int mmTPC_PLL_CLK_RLX_0 ; 

__attribute__((used)) static void goya_init_protection_bits(struct hl_device *hdev)
{
	/*
	 * In each 4K block of registers, the last 128 bytes are protection
	 * bits - total of 1024 bits, one for each register. Each bit is related
	 * to a specific register, by the order of the registers.
	 * So in order to calculate the bit that is related to a given register,
	 * we need to calculate its word offset and then the exact bit inside
	 * the word (which is 4 bytes).
	 *
	 * Register address:
	 *
	 * 31                 12 11           7   6             2  1      0
	 * -----------------------------------------------------------------
	 * |      Don't         |    word       |  bit location  |    0    |
	 * |      care          |   offset      |  inside word   |         |
	 * -----------------------------------------------------------------
	 *
	 * Bits 7-11 represents the word offset inside the 128 bytes.
	 * Bits 2-6 represents the bit location inside the word.
	 */
	u32 pb_addr, mask;
	u8 word_offset;

	goya_pb_set_block(hdev, mmPCI_NRTR_BASE);
	goya_pb_set_block(hdev, mmPCI_RD_REGULATOR_BASE);
	goya_pb_set_block(hdev, mmPCI_WR_REGULATOR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y0_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y0_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y1_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y1_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y2_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y2_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y3_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y3_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y4_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y4_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmSRAM_Y5_X0_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X0_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X1_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X1_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X2_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X2_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X3_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X3_RTR_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X4_BANK_BASE);
	goya_pb_set_block(hdev, mmSRAM_Y5_X4_RTR_BASE);

	goya_pb_set_block(hdev, mmPCIE_WRAP_BASE);
	goya_pb_set_block(hdev, mmPCIE_CORE_BASE);
	goya_pb_set_block(hdev, mmPCIE_DB_CFG_BASE);
	goya_pb_set_block(hdev, mmPCIE_DB_CMD_BASE);
	goya_pb_set_block(hdev, mmPCIE_AUX_BASE);
	goya_pb_set_block(hdev, mmPCIE_DB_RSV_BASE);
	goya_pb_set_block(hdev, mmPCIE_PHY_BASE);
	goya_pb_set_block(hdev, mmTPC0_NRTR_BASE);
	goya_pb_set_block(hdev, mmTPC_PLL_BASE);

	pb_addr = (mmTPC_PLL_CLK_RLX_0 & ~0xFFF) + PROT_BITS_OFFS;
	word_offset = ((mmTPC_PLL_CLK_RLX_0 & PROT_BITS_OFFS) >> 7) << 2;
	mask = 1 << ((mmTPC_PLL_CLK_RLX_0 & 0x7C) >> 2);

	WREG32(pb_addr + word_offset, mask);

	goya_init_mme_protection_bits(hdev);

	goya_init_dma_protection_bits(hdev);

	goya_init_tpc_protection_bits(hdev);
}