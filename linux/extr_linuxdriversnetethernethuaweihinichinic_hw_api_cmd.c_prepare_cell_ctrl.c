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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SZ ; 
 int HINIC_API_CMD_CELL_CTRL_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD_DMA_ATTR ; 
 int /*<<< orphan*/  RD_DMA_ATTR_DEFAULT ; 
 int /*<<< orphan*/  SIZE_8BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR_DMA_ATTR ; 
 int /*<<< orphan*/  WR_DMA_ATTR_DEFAULT ; 
 int /*<<< orphan*/  XOR_CHKSUM ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  xor_chksum_set (int*) ; 

__attribute__((used)) static void prepare_cell_ctrl(u64 *cell_ctrl, u16 data_size)
{
	u8 chksum;
	u64 ctrl;

	ctrl =  HINIC_API_CMD_CELL_CTRL_SET(SIZE_8BYTES(data_size), DATA_SZ)  |
		HINIC_API_CMD_CELL_CTRL_SET(RD_DMA_ATTR_DEFAULT, RD_DMA_ATTR) |
		HINIC_API_CMD_CELL_CTRL_SET(WR_DMA_ATTR_DEFAULT, WR_DMA_ATTR);

	chksum = xor_chksum_set(&ctrl);

	ctrl |= HINIC_API_CMD_CELL_CTRL_SET(chksum, XOR_CHKSUM);

	/* The data in the HW should be in Big Endian Format */
	*cell_ctrl = cpu_to_be64(ctrl);
}