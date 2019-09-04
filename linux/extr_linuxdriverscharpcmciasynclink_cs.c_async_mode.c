#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int data_rate; int data_bits; int stop_bits; scalar_t__ parity; int flags; scalar_t__ loopback; } ;
struct TYPE_16__ {int serial_signals; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ ASYNC_PARITY_NONE ; 
 scalar_t__ ASYNC_PARITY_ODD ; 
 unsigned char BIT0 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 scalar_t__ CCR0 ; 
 scalar_t__ CCR1 ; 
 scalar_t__ CCR2 ; 
 scalar_t__ CCR3 ; 
 scalar_t__ CCR4 ; 
 scalar_t__ CHA ; 
 scalar_t__ CHB ; 
 scalar_t__ CMD_RXRESET ; 
 scalar_t__ CMD_TXRESET ; 
 scalar_t__ DAFO ; 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int IRQ_ALLSENT ; 
 int IRQ_BREAK_ON ; 
 int IRQ_CTS ; 
 int IRQ_RXEOM ; 
 int IRQ_RXFIFO ; 
 int IRQ_RXTIME ; 
 int IRQ_TXFIFO ; 
 scalar_t__ ISR ; 
 scalar_t__ MODE ; 
 scalar_t__ PVR ; 
 scalar_t__ RFC ; 
 scalar_t__ RLCR ; 
 int SerialSignal_RTS ; 
 scalar_t__ XBCH ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_2__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  enable_auxclk (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_disable (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  irq_enable (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  issue_command (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mgslpc_set_rate (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  port_irq_disable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  read_reg16 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  set_reg_bits (TYPE_2__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  wait_command_complete (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void async_mode(MGSLPC_INFO *info)
{
	unsigned char val;

	/* disable all interrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* MODE
	 *
	 * 07      Reserved, 0
	 * 06      FRTS RTS State, 0=active
	 * 05      FCTS Flow Control on CTS
	 * 04      FLON Flow Control Enable
	 * 03      RAC Receiver Active, 0 = inactive
	 * 02      RTS 0=Auto RTS, 1=manual RTS
	 * 01      TRS Timer Resolution, 1=512
	 * 00      TLP Test Loop, 0 = no loop
	 *
	 * 0000 0110
	 */
	val = 0x06;
	if (info->params.loopback)
		val |= BIT0;

	/* preserve RTS state */
	if (!(info->serial_signals & SerialSignal_RTS))
		val |= BIT6;
	write_reg(info, CHA + MODE, val);

	/* CCR0
	 *
	 * 07      PU Power Up, 1=active, 0=power down
	 * 06      MCE Master Clock Enable, 1=enabled
	 * 05      Reserved, 0
	 * 04..02  SC[2..0] Encoding, 000=NRZ
	 * 01..00  SM[1..0] Serial Mode, 11=Async
	 *
	 * 1000 0011
	 */
	write_reg(info, CHA + CCR0, 0x83);

	/* CCR1
	 *
	 * 07..05  Reserved, 0
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      BCR Bit Clock Rate, 1=16x
	 * 02..00  CM[2..0] Clock Mode, 111=BRG
	 *
	 * 0001 1111
	 */
	write_reg(info, CHA + CCR1, 0x1f);

	/* CCR2 (channel A)
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate divisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 0=TxCLK is input
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      Reserved, 0
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0001 0000
	 */
	write_reg(info, CHA + CCR2, 0x10);

	/* CCR3
	 *
	 * 07..01  Reserved, 0
	 * 00      PSD DPLL Phase Shift Disable
	 *
	 * 0000 0000
	 */
	write_reg(info, CHA + CCR3, 0);

	/* CCR4
	 *
	 * 07      MCK4 Master Clock Divide by 4, 1=enabled
	 * 06      EBRG Enhanced Baud Rate Generator Mode, 1=enabled
	 * 05      TST1 Test Pin, 0=normal operation
	 * 04      ICD Ivert Carrier Detect, 1=enabled (active low)
	 * 03..00  Reserved, must be 0
	 *
	 * 0101 0000
	 */
	write_reg(info, CHA + CCR4, 0x50);
	mgslpc_set_rate(info, CHA, info->params.data_rate * 16);

	/* DAFO Data Format
	 *
	 * 07      Reserved, 0
	 * 06      XBRK transmit break, 0=normal operation
	 * 05      Stop bits (0=1, 1=2)
	 * 04..03  PAR[1..0] Parity (01=odd, 10=even)
	 * 02      PAREN Parity Enable
	 * 01..00  CHL[1..0] Character Length (00=8, 01=7)
	 *
	 */
	val = 0x00;
	if (info->params.data_bits != 8)
		val |= BIT0;	/* 7 bits */
	if (info->params.stop_bits != 1)
		val |= BIT5;
	if (info->params.parity != ASYNC_PARITY_NONE)
	{
		val |= BIT2;	/* Parity enable */
		if (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT3;
		else
			val |= BIT4;
	}
	write_reg(info, CHA + DAFO, val);

	/* RFC Rx FIFO Control
	 *
	 * 07      Reserved, 0
	 * 06      DPS, 1=parity bit not stored in data byte
	 * 05      DXS, 0=all data stored in FIFO (including XON/XOFF)
	 * 04      RFDF Rx FIFO Data Format, 1=status byte stored in FIFO
	 * 03..02  RFTH[1..0], rx threshold, 11=16 status + 16 data byte
	 * 01      Reserved, 0
	 * 00      TCDE Terminate Char Detect Enable, 0=disabled
	 *
	 * 0101 1100
	 */
	write_reg(info, CHA + RFC, 0x5c);

	/* RLCR Receive length check register
	 *
	 * Max frame length = (RL + 1) * 32
	 */
	write_reg(info, CHA + RLCR, 0);

	/* XBCH Transmit Byte Count High
	 *
	 * 07      DMA mode, 0 = interrupt driven
	 * 06      NRM, 0=ABM (ignored)
	 * 05      CAS Carrier Auto Start
	 * 04      XC Transmit Continuously (ignored)
	 * 03..00  XBC[10..8] Transmit byte count bits 10..8
	 *
	 * 0000 0000
	 */
	val = 0x00;
	if (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT5;
	write_reg(info, CHA + XBCH, val);
	if (info->params.flags & HDLC_FLAG_AUTO_CTS)
		irq_enable(info, CHA, IRQ_CTS);

	/* MODE:03 RAC Receiver Active, 1=active */
	set_reg_bits(info, CHA + MODE, BIT3);
	enable_auxclk(info);
	if (info->params.flags & HDLC_FLAG_AUTO_CTS) {
		irq_enable(info, CHB, IRQ_CTS);
		/* PVR[3] 1=AUTO CTS active */
		set_reg_bits(info, CHA + PVR, BIT3);
	} else
		clear_reg_bits(info, CHA + PVR, BIT3);
	irq_enable(info, CHA,
			  IRQ_RXEOM | IRQ_RXFIFO | IRQ_BREAK_ON | IRQ_RXTIME |
			  IRQ_ALLSENT | IRQ_TXFIFO);
	issue_command(info, CHA, CMD_TXRESET + CMD_RXRESET);
	wait_command_complete(info, CHA);
	read_reg16(info, CHA + ISR);	/* clear pending IRQs */
}