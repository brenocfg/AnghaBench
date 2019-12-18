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

__attribute__((used)) static u16 ad7616_spi_rd_wr_cmd(int addr, char isWriteOp)
{
	/*
	 * The address of register consist of one w/r bit
	 * 6 bits of address followed by one reserved bit.
	 */
	return ((addr & 0x7F) << 1) | ((isWriteOp & 0x1) << 7);
}