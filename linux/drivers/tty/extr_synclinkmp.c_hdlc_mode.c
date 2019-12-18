#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int flags; scalar_t__ crc_type; int encoding; int clock_speed; scalar_t__ loopback; } ;
struct TYPE_14__ {int port_num; int buffer_list_phys; unsigned char ie0_value; int serial_signals; TYPE_2__ params; TYPE_1__** port_array; } ;
struct TYPE_12__ {int ctrlreg_value; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 int BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 unsigned char BIT7 ; 
 scalar_t__ CPB ; 
 scalar_t__ CTL ; 
 scalar_t__ DIR ; 
 scalar_t__ DMR ; 
 scalar_t__ HDLC_CRC_16_CCITT ; 
#define  HDLC_ENCODING_BIPHASE_LEVEL 134 
#define  HDLC_ENCODING_BIPHASE_MARK 133 
#define  HDLC_ENCODING_BIPHASE_SPACE 132 
#define  HDLC_ENCODING_DIFF_BIPHASE_LEVEL 131 
#define  HDLC_ENCODING_NRZB 130 
#define  HDLC_ENCODING_NRZI 129 
#define  HDLC_ENCODING_NRZI_MARK 128 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int HDLC_FLAG_DPLL_DIV16 ; 
 int HDLC_FLAG_DPLL_DIV8 ; 
 int HDLC_FLAG_RXC_BRG ; 
 int HDLC_FLAG_RXC_DPLL ; 
 int HDLC_FLAG_TXC_BRG ; 
 int HDLC_FLAG_TXC_DPLL ; 
 scalar_t__ IE0 ; 
 scalar_t__ MD0 ; 
 scalar_t__ MD1 ; 
 scalar_t__ MD2 ; 
 scalar_t__ RRC ; 
 scalar_t__ RXDMA ; 
 unsigned char RXINTE ; 
 scalar_t__ RXS ; 
 int SerialSignal_RTS ; 
 scalar_t__ TRC0 ; 
 scalar_t__ TRC1 ; 
 scalar_t__ TXDMA ; 
 unsigned char TXINTE ; 
 scalar_t__ TXS ; 
 int /*<<< orphan*/  enable_loopback (TYPE_3__*,int) ; 
 unsigned char rx_active_fifo_level ; 
 int /*<<< orphan*/  rx_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  set_rate (TYPE_3__*,int) ; 
 unsigned char tx_active_fifo_level ; 
 int tx_negate_fifo_level ; 
 int /*<<< orphan*/  tx_set_idle (TYPE_3__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  write_control_reg (TYPE_3__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_3__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void hdlc_mode(SLMP_INFO *info)
{
	unsigned char RegValue;
	u32 DpllDivisor;

	// Can't use DPLL because SCA outputs recovered clock on RxC when
	// DPLL mode selected. This causes output contention with RxC receiver.
	// Use of DPLL would require external hardware to disable RxC receiver
	// when DPLL mode selected.
	info->params.flags &= ~(HDLC_FLAG_TXC_DPLL + HDLC_FLAG_RXC_DPLL);

	/* disable DMA interrupts */
	write_reg(info, TXDMA + DIR, 0);
	write_reg(info, RXDMA + DIR, 0);

	/* MD0, Mode Register 0
	 *
	 * 07..05  PRCTL<2..0>, Protocol Mode, 100=HDLC
	 * 04      AUTO, Auto-enable (RTS/CTS/DCD)
	 * 03      Reserved, must be 0
	 * 02      CRCCC, CRC Calculation, 1=enabled
	 * 01      CRC1, CRC selection, 0=CRC-16,1=CRC-CCITT-16
	 * 00      CRC0, CRC initial value, 1 = all 1s
	 *
	 * 1000 0001
	 */
	RegValue = 0x81;
	if (info->params.flags & HDLC_FLAG_AUTO_CTS)
		RegValue |= BIT4;
	if (info->params.flags & HDLC_FLAG_AUTO_DCD)
		RegValue |= BIT4;
	if (info->params.crc_type == HDLC_CRC_16_CCITT)
		RegValue |= BIT2 + BIT1;
	write_reg(info, MD0, RegValue);

	/* MD1, Mode Register 1
	 *
	 * 07..06  ADDRS<1..0>, Address detect, 00=no addr check
	 * 05..04  TXCHR<1..0>, tx char size, 00=8 bits
	 * 03..02  RXCHR<1..0>, rx char size, 00=8 bits
	 * 01..00  PMPM<1..0>, Parity mode, 00=no parity
	 *
	 * 0000 0000
	 */
	RegValue = 0x00;
	write_reg(info, MD1, RegValue);

	/* MD2, Mode Register 2
	 *
	 * 07      NRZFM, 0=NRZ, 1=FM
	 * 06..05  CODE<1..0> Encoding, 00=NRZ
	 * 04..03  DRATE<1..0> DPLL Divisor, 00=8
	 * 02      Reserved, must be 0
	 * 01..00  CNCT<1..0> Channel connection, 0=normal
	 *
	 * 0000 0000
	 */
	RegValue = 0x00;
	switch(info->params.encoding) {
	case HDLC_ENCODING_NRZI:	  RegValue |= BIT5; break;
	case HDLC_ENCODING_BIPHASE_MARK:  RegValue |= BIT7 + BIT5; break; /* aka FM1 */
	case HDLC_ENCODING_BIPHASE_SPACE: RegValue |= BIT7 + BIT6; break; /* aka FM0 */
	case HDLC_ENCODING_BIPHASE_LEVEL: RegValue |= BIT7; break; 	/* aka Manchester */
#if 0
	case HDLC_ENCODING_NRZB:	       				/* not supported */
	case HDLC_ENCODING_NRZI_MARK:          				/* not supported */
	case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: 				/* not supported */
#endif
	}
	if ( info->params.flags & HDLC_FLAG_DPLL_DIV16 ) {
		DpllDivisor = 16;
		RegValue |= BIT3;
	} else if ( info->params.flags & HDLC_FLAG_DPLL_DIV8 ) {
		DpllDivisor = 8;
	} else {
		DpllDivisor = 32;
		RegValue |= BIT4;
	}
	write_reg(info, MD2, RegValue);


	/* RXS, Receive clock source
	 *
	 * 07      Reserved, must be 0
	 * 06..04  RXCS<2..0>, clock source, 000=RxC Pin, 100=BRG, 110=DPLL
	 * 03..00  RXBR<3..0>, rate divisor, 0000=1
	 */
	RegValue=0;
	if (info->params.flags & HDLC_FLAG_RXC_BRG)
		RegValue |= BIT6;
	if (info->params.flags & HDLC_FLAG_RXC_DPLL)
		RegValue |= BIT6 + BIT5;
	write_reg(info, RXS, RegValue);

	/* TXS, Transmit clock source
	 *
	 * 07      Reserved, must be 0
	 * 06..04  RXCS<2..0>, clock source, 000=TxC Pin, 100=BRG, 110=Receive Clock
	 * 03..00  RXBR<3..0>, rate divisor, 0000=1
	 */
	RegValue=0;
	if (info->params.flags & HDLC_FLAG_TXC_BRG)
		RegValue |= BIT6;
	if (info->params.flags & HDLC_FLAG_TXC_DPLL)
		RegValue |= BIT6 + BIT5;
	write_reg(info, TXS, RegValue);

	if (info->params.flags & HDLC_FLAG_RXC_DPLL)
		set_rate(info, info->params.clock_speed * DpllDivisor);
	else
		set_rate(info, info->params.clock_speed);

	/* GPDATA (General Purpose I/O Data Register)
	 *
	 * 6,4,2,0  CLKSEL<3..0>, 0 = TcCLK in, 1 = Auxclk out
	 */
	if (info->params.flags & HDLC_FLAG_TXC_BRG)
		info->port_array[0]->ctrlreg_value |= (BIT0 << (info->port_num * 2));
	else
		info->port_array[0]->ctrlreg_value &= ~(BIT0 << (info->port_num * 2));
	write_control_reg(info);

	/* RRC Receive Ready Control 0
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  RRC<4..0> Rx FIFO trigger active
	 */
	write_reg(info, RRC, rx_active_fifo_level);

	/* TRC0 Transmit Ready Control 0
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  TRC<4..0> Tx FIFO trigger active
	 */
	write_reg(info, TRC0, tx_active_fifo_level);

	/* TRC1 Transmit Ready Control 1
	 *
	 * 07..05  Reserved, must be 0
	 * 04..00  TRC<4..0> Tx FIFO trigger inactive 0x1f = 32 bytes (full)
	 */
	write_reg(info, TRC1, (unsigned char)(tx_negate_fifo_level - 1));

	/* DMR, DMA Mode Register
	 *
	 * 07..05  Reserved, must be 0
	 * 04      TMOD, Transfer Mode: 1=chained-block
	 * 03      Reserved, must be 0
	 * 02      NF, Number of Frames: 1=multi-frame
	 * 01      CNTE, Frame End IRQ Counter enable: 0=disabled
	 * 00      Reserved, must be 0
	 *
	 * 0001 0100
	 */
	write_reg(info, TXDMA + DMR, 0x14);
	write_reg(info, RXDMA + DMR, 0x14);

	/* Set chain pointer base (upper 8 bits of 24 bit addr) */
	write_reg(info, RXDMA + CPB,
		(unsigned char)(info->buffer_list_phys >> 16));

	/* Set chain pointer base (upper 8 bits of 24 bit addr) */
	write_reg(info, TXDMA + CPB,
		(unsigned char)(info->buffer_list_phys >> 16));

	/* enable status interrupts. other code enables/disables
	 * the individual sources for these two interrupt classes.
	 */
	info->ie0_value |= TXINTE + RXINTE;
	write_reg(info, IE0, info->ie0_value);

	/* CTL, MSCI control register
	 *
	 * 07..06  Reserved, set to 0
	 * 05      UDRNC, underrun control, 0=abort 1=CRC+flag (HDLC/BSC)
	 * 04      IDLC, idle control, 0=mark 1=idle register
	 * 03      BRK, break, 0=off 1 =on (async)
	 * 02      SYNCLD, sync char load enable (BSC) 1=enabled
	 * 01      GOP, go active on poll (LOOP mode) 1=enabled
	 * 00      RTS, RTS output control, 0=active 1=inactive
	 *
	 * 0001 0001
	 */
	RegValue = 0x10;
	if (!(info->serial_signals & SerialSignal_RTS))
		RegValue |= 0x01;
	write_reg(info, CTL, RegValue);

	/* preamble not supported ! */

	tx_set_idle(info);
	tx_stop(info);
	rx_stop(info);

	set_rate(info, info->params.clock_speed);

	if (info->params.loopback)
		enable_loopback(info,1);
}