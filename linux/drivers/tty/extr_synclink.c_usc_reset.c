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
struct mgsl_struct {scalar_t__ bus_type; scalar_t__ io_base; scalar_t__ usc_idle_mode; scalar_t__ loopback_bits; scalar_t__ mbre_bit; int /*<<< orphan*/  misc_ctrl_value; scalar_t__ lcr_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT30 ; 
 int /*<<< orphan*/  BUS_DESCRIPTOR (int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CCAR ; 
 int /*<<< orphan*/  IOCR ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  RTCmd_SelectLittleEndian ; 
 scalar_t__ SDPIN ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_reset( struct mgsl_struct *info )
{
	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		int i;
		u32 readval;

		/* Set BIT30 of Misc Control Register */
		/* (Local Control Register 0x50) to force reset of USC. */

		volatile u32 *MiscCtrl = (u32 *)(info->lcr_base + 0x50);
		u32 *LCR0BRDR = (u32 *)(info->lcr_base + 0x28);

		info->misc_ctrl_value |= BIT30;
		*MiscCtrl = info->misc_ctrl_value;

		/*
		 * Force at least 170ns delay before clearing 
		 * reset bit. Each read from LCR takes at least 
		 * 30ns so 10 times for 300ns to be safe.
		 */
		for(i=0;i<10;i++)
			readval = *MiscCtrl;

		info->misc_ctrl_value &= ~BIT30;
		*MiscCtrl = info->misc_ctrl_value;

		*LCR0BRDR = BUS_DESCRIPTOR(
			1,		// Write Strobe Hold (0-3)
			2,		// Write Strobe Delay (0-3)
			2,		// Read Strobe Delay  (0-3)
			0,		// NWDD (Write data-data) (0-3)
			4,		// NWAD (Write Addr-data) (0-31)
			0,		// NXDA (Read/Write Data-Addr) (0-3)
			0,		// NRDD (Read Data-Data) (0-3)
			5		// NRAD (Read Addr-Data) (0-31)
			);
	} else {
		/* do HW reset */
		outb( 0,info->io_base + 8 );
	}

	info->mbre_bit = 0;
	info->loopback_bits = 0;
	info->usc_idle_mode = 0;

	/*
	 * Program the Bus Configuration Register (BCR)
	 *
	 * <15>		0	Don't use separate address
	 * <14..6>	0	reserved
	 * <5..4>	00	IAckmode = Default, don't care
	 * <3>		1	Bus Request Totem Pole output
	 * <2>		1	Use 16 Bit data bus
	 * <1>		0	IRQ Totem Pole output
	 * <0>		0	Don't Shift Right Addr
	 *
	 * 0000 0000 0000 1100 = 0x000c
	 *
	 * By writing to io_base + SDPIN the Wait/Ack pin is
	 * programmed to work as a Wait pin.
	 */
	
	outw( 0x000c,info->io_base + SDPIN );


	outw( 0,info->io_base );
	outw( 0,info->io_base + CCAR );

	/* select little endian byte ordering */
	usc_RTCmd( info, RTCmd_SelectLittleEndian );


	/* Port Control Register (PCR)
	 *
	 * <15..14>	11	Port 7 is Output (~DMAEN, Bit 14 : 0 = Enabled)
	 * <13..12>	11	Port 6 is Output (~INTEN, Bit 12 : 0 = Enabled)
	 * <11..10> 	00	Port 5 is Input (No Connect, Don't Care)
	 * <9..8> 	00	Port 4 is Input (No Connect, Don't Care)
	 * <7..6>	11	Port 3 is Output (~RTS, Bit 6 : 0 = Enabled )
	 * <5..4>	11	Port 2 is Output (~DTR, Bit 4 : 0 = Enabled )
	 * <3..2>	01	Port 1 is Input (Dedicated RxC)
	 * <1..0>	01	Port 0 is Input (Dedicated TxC)
	 *
	 *	1111 0000 1111 0101 = 0xf0f5
	 */

	usc_OutReg( info, PCR, 0xf0f5 );


	/*
	 * Input/Output Control Register
	 *
	 * <15..14>	00	CTS is active low input
	 * <13..12>	00	DCD is active low input
	 * <11..10>	00	TxREQ pin is input (DSR)
	 * <9..8>	00	RxREQ pin is input (RI)
	 * <7..6>	00	TxD is output (Transmit Data)
	 * <5..3>	000	TxC Pin in Input (14.7456MHz Clock)
	 * <2..0>	100	RxC is Output (drive with BRG0)
	 *
	 *	0000 0000 0000 0100 = 0x0004
	 */

	usc_OutReg( info, IOCR, 0x0004 );

}