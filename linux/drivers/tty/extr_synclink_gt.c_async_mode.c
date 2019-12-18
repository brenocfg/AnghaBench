#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ parity; int data_bits; int stop_bits; int flags; int data_rate; scalar_t__ loopback; } ;
struct slgt_info {int if_mode; int base_clock; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ ASYNC_PARITY_NONE ; 
 scalar_t__ ASYNC_PARITY_ODD ; 
 unsigned short BIT0 ; 
 unsigned short BIT14 ; 
 unsigned short BIT15 ; 
 unsigned short BIT3 ; 
 unsigned short BIT4 ; 
 unsigned short BIT5 ; 
 unsigned short BIT7 ; 
 unsigned short BIT8 ; 
 unsigned short BIT9 ; 
 int /*<<< orphan*/  CCR ; 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int IRQ_ALL ; 
 int IRQ_MASTER ; 
 int IRQ_RXBREAK ; 
 int IRQ_RXOVER ; 
 int /*<<< orphan*/  JCR ; 
 int MGSL_INTERFACE_RTS_EN ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  SCR ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  enable_loopback (struct slgt_info*) ; 
 int /*<<< orphan*/  msc_set_vcr (struct slgt_info*) ; 
 unsigned short rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  set_rate (struct slgt_info*,int) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int) ; 
 int /*<<< orphan*/  slgt_irq_on (struct slgt_info*,int) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg8 (struct slgt_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void async_mode(struct slgt_info *info)
{
  	unsigned short val;

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
	tx_stop(info);
	rx_stop(info);

	/* TCR (tx control)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NRZ
	 * 09      parity enable
	 * 08      1=odd parity, 0=even parity
	 * 07      1=RTS driver control
	 * 06      1=break enable
	 * 05..04  character length
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      0=1 stop bit, 1=2 stop bits
	 * 02      reset
	 * 01      enable
	 * 00      auto-CTS enable
	 */
	val = 0x4000;

	if (info->if_mode & MGSL_INTERFACE_RTS_EN)
		val |= BIT7;

	if (info->params.parity != ASYNC_PARITY_NONE) {
		val |= BIT9;
		if (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT8;
	}

	switch (info->params.data_bits)
	{
	case 6: val |= BIT4; break;
	case 7: val |= BIT5; break;
	case 8: val |= BIT5 + BIT4; break;
	}

	if (info->params.stop_bits != 1)
		val |= BIT3;

	if (info->params.flags & HDLC_FLAG_AUTO_CTS)
		val |= BIT0;

	wr_reg16(info, TCR, val);

	/* RCR (rx control)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NRZ
	 * 09      parity enable
	 * 08      1=odd parity, 0=even parity
	 * 07..06  reserved, must be 0
	 * 05..04  character length
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      reserved, must be zero
	 * 02      reset
	 * 01      enable
	 * 00      auto-DCD enable
	 */
	val = 0x4000;

	if (info->params.parity != ASYNC_PARITY_NONE) {
		val |= BIT9;
		if (info->params.parity == ASYNC_PARITY_ODD)
			val |= BIT8;
	}

	switch (info->params.data_bits)
	{
	case 6: val |= BIT4; break;
	case 7: val |= BIT5; break;
	case 8: val |= BIT5 + BIT4; break;
	}

	if (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT0;

	wr_reg16(info, RCR, val);

	/* CCR (clock control)
	 *
	 * 07..05  011 = tx clock source is BRG/16
	 * 04..02  010 = rx clock source is BRG
	 * 01      0 = auxclk disabled
	 * 00      1 = BRG enabled
	 *
	 * 0110 1001
	 */
	wr_reg8(info, CCR, 0x69);

	msc_set_vcr(info);

	/* SCR (serial control)
	 *
	 * 15  1=tx req on FIFO half empty
	 * 14  1=rx req on FIFO half full
	 * 13  tx data  IRQ enable
	 * 12  tx idle  IRQ enable
	 * 11  rx break on IRQ enable
	 * 10  rx data  IRQ enable
	 * 09  rx break off IRQ enable
	 * 08  overrun  IRQ enable
	 * 07  DSR      IRQ enable
	 * 06  CTS      IRQ enable
	 * 05  DCD      IRQ enable
	 * 04  RI       IRQ enable
	 * 03  0=16x sampling, 1=8x sampling
	 * 02  1=txd->rxd internal loopback enable
	 * 01  reserved, must be zero
	 * 00  1=master IRQ enable
	 */
	val = BIT15 + BIT14 + BIT0;
	/* JCR[8] : 1 = x8 async mode feature available */
	if ((rd_reg32(info, JCR) & BIT8) && info->params.data_rate &&
	    ((info->base_clock < (info->params.data_rate * 16)) ||
	     (info->base_clock % (info->params.data_rate * 16)))) {
		/* use 8x sampling */
		val |= BIT3;
		set_rate(info, info->params.data_rate * 8);
	} else {
		/* use 16x sampling */
		set_rate(info, info->params.data_rate * 16);
	}
	wr_reg16(info, SCR, val);

	slgt_irq_on(info, IRQ_RXBREAK | IRQ_RXOVER);

	if (info->params.loopback)
		enable_loopback(info);
}