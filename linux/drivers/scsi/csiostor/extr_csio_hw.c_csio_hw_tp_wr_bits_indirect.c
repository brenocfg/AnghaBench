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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_PIO_ADDR_A ; 
 int /*<<< orphan*/  TP_PIO_DATA_A ; 
 unsigned int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,unsigned int,int /*<<< orphan*/ ) ; 

void
csio_hw_tp_wr_bits_indirect(struct csio_hw *hw, unsigned int addr,
			unsigned int mask, unsigned int val)
{
	csio_wr_reg32(hw, addr, TP_PIO_ADDR_A);
	val |= csio_rd_reg32(hw, TP_PIO_DATA_A) & ~mask;
	csio_wr_reg32(hw, val, TP_PIO_DATA_A);
}