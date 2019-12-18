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
typedef  int u16 ;
struct TYPE_2__ {int clock_speed; } ;
struct mgsl_struct {scalar_t__ bus_type; int loopback_bits; scalar_t__ io_base; TYPE_1__ params; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 int BIT6 ; 
 int BIT7 ; 
 scalar_t__ CCAR ; 
 int /*<<< orphan*/  CMCR ; 
 int /*<<< orphan*/  HCR ; 
 int /*<<< orphan*/  IOCR ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  TC0R ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usc_enable_loopback(struct mgsl_struct *info, int enable)
{
	if (enable) {
		/* blank external TXD output */
		usc_OutReg(info,IOCR,usc_InReg(info,IOCR) | (BIT7 | BIT6));
	
		/* Clock mode Control Register (CMCR)
		 *
		 * <15..14>	00	counter 1 Disabled
		 * <13..12> 	00	counter 0 Disabled
		 * <11..10> 	11	BRG1 Input is TxC Pin
		 * <9..8>	11	BRG0 Input is TxC Pin
		 * <7..6>	01	DPLL Input is BRG1 Output
		 * <5..3>	100	TxCLK comes from BRG0
		 * <2..0>   	100	RxCLK comes from BRG0
		 *
		 * 0000 1111 0110 0100 = 0x0f64
		 */

		usc_OutReg( info, CMCR, 0x0f64 );

		/* Write 16-bit Time Constant for BRG0 */
		/* use clock speed if available, otherwise use 8 for diagnostics */
		if (info->params.clock_speed) {
			if (info->bus_type == MGSL_BUS_TYPE_PCI)
				usc_OutReg(info, TC0R, (u16)((11059200/info->params.clock_speed)-1));
			else
				usc_OutReg(info, TC0R, (u16)((14745600/info->params.clock_speed)-1));
		} else
			usc_OutReg(info, TC0R, (u16)8);

		/* Hardware Configuration Register (HCR) Clear Bit 1, BRG0
		   mode = Continuous Set Bit 0 to enable BRG0.  */
		usc_OutReg( info, HCR, (u16)((usc_InReg( info, HCR ) & ~BIT1) | BIT0) );

		/* Input/Output Control Reg, <2..0> = 100, Drive RxC pin with BRG0 */
		usc_OutReg(info, IOCR, (u16)((usc_InReg(info, IOCR) & 0xfff8) | 0x0004));

		/* set Internal Data loopback mode */
		info->loopback_bits = 0x300;
		outw( 0x0300, info->io_base + CCAR );
	} else {
		/* enable external TXD output */
		usc_OutReg(info,IOCR,usc_InReg(info,IOCR) & ~(BIT7 | BIT6));
	
		/* clear Internal Data loopback mode */
		info->loopback_bits = 0;
		outw( 0,info->io_base + CCAR );
	}
	
}