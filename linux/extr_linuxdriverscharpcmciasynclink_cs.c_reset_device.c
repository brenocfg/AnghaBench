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
typedef  int /*<<< orphan*/  MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ CCR0 ; 
 scalar_t__ CHA ; 
 scalar_t__ CHB ; 
 scalar_t__ IPC ; 
 scalar_t__ MODE ; 
 scalar_t__ PCR ; 
 int /*<<< orphan*/  irq_disable (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  port_irq_disable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void reset_device(MGSLPC_INFO *info)
{
	/* power up both channels (set BIT7) */
	write_reg(info, CHA + CCR0, 0x80);
	write_reg(info, CHB + CCR0, 0x80);
	write_reg(info, CHA + MODE, 0);
	write_reg(info, CHB + MODE, 0);

	/* disable all interrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* PCR Port Configuration Register
	 *
	 * 07..04  DEC[3..0] Serial I/F select outputs
	 * 03      output, 1=AUTO CTS control enabled
	 * 02      RI Ring Indicator input 0=active
	 * 01      DSR input 0=active
	 * 00      DTR output 0=active
	 *
	 * 0000 0110
	 */
	write_reg(info, PCR, 0x06);

	/* PVR Port Value Register
	 *
	 * 07..04  DEC[3..0] Serial I/F select (0000=disabled)
	 * 03      AUTO CTS output 1=enabled
	 * 02      RI Ring Indicator input
	 * 01      DSR input
	 * 00      DTR output (1=inactive)
	 *
	 * 0000 0001
	 */
//	write_reg(info, PVR, PVR_DTR);

	/* IPC Interrupt Port Configuration
	 *
	 * 07      VIS 1=Masked interrupts visible
	 * 06..05  Reserved, 0
	 * 04..03  SLA Slave address, 00 ignored
	 * 02      CASM Cascading Mode, 1=daisy chain
	 * 01..00  IC[1..0] Interrupt Config, 01=push-pull output, active low
	 *
	 * 0000 0101
	 */
	write_reg(info, IPC, 0x05);
}