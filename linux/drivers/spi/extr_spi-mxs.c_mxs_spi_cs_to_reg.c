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

/* Variables and functions */
 int /*<<< orphan*/  BM_SSP_CTRL0_WAIT_FOR_CMD ; 
 int /*<<< orphan*/  BM_SSP_CTRL0_WAIT_FOR_IRQ ; 

__attribute__((used)) static u32 mxs_spi_cs_to_reg(unsigned cs)
{
	u32 select = 0;

	/*
	 * i.MX28 Datasheet: 17.10.1: HW_SSP_CTRL0
	 *
	 * The bits BM_SSP_CTRL0_WAIT_FOR_CMD and BM_SSP_CTRL0_WAIT_FOR_IRQ
	 * in HW_SSP_CTRL0 register do have multiple usage, please refer to
	 * the datasheet for further details. In SPI mode, they are used to
	 * toggle the chip-select lines (nCS pins).
	 */
	if (cs & 1)
		select |= BM_SSP_CTRL0_WAIT_FOR_CMD;
	if (cs & 2)
		select |= BM_SSP_CTRL0_WAIT_FOR_IRQ;

	return select;
}