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
 int /*<<< orphan*/  IRDA_IO_BASE ; 
 int /*<<< orphan*/  wb977_device_enable () ; 
 int /*<<< orphan*/  wb977_device_select (int) ; 
 int /*<<< orphan*/  wb977_wb (int,int) ; 
 int /*<<< orphan*/  wb977_ww (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wb977_init_irda(void)
{
	wb977_device_select(6);

	/*
	 * IR base address
	 */
	wb977_ww(0x60, IRDA_IO_BASE);

	/*
	 * IRDA IRQ 6, active high, edge trigger
	 */
	wb977_wb(0x70, 6);
	wb977_wb(0x71, 0x02);

	/*
	 * RX DMA - ISA DMA 0
	 */
	wb977_wb(0x74, 0x00);

	/*
	 * TX DMA - Disable Tx DMA
	 */
	wb977_wb(0x75, 0x04);

	/*
	 * Append CRC, Enable bank selection
	 */
	wb977_wb(0xf0, 0x03);

	/*
	 * Enable device
	 */
	wb977_device_enable();
}