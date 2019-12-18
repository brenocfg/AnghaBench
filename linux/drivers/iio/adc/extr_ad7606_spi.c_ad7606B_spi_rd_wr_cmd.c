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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 ad7606B_spi_rd_wr_cmd(int addr, char is_write_op)
{
	/*
	 * The address of register consists of one bit which
	 * specifies a read command placed in bit 6, followed by
	 * 6 bits of address.
	 */
	return (addr & 0x3F) | (((~is_write_op) & 0x1) << 6);
}