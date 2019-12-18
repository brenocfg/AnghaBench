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
struct TYPE_2__ {int read_status_mask; int ignore_status_mask; } ;
struct uart_ip22zilog_port {int* curregs; int parity_mask; TYPE_1__ port; } ;

/* Variables and functions */
 int BRENAB ; 
 unsigned int BRKINT ; 
 int BRK_ABRT ; 
 int CRC_ERR ; 
 unsigned int CREAD ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int IGNBRK ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 int NRZ ; 
 unsigned int PARENB ; 
 unsigned int PARMRK ; 
 unsigned int PARODD ; 
 int PAR_ENAB ; 
 int PAR_ERR ; 
 int PAR_EVEN ; 
 size_t R10 ; 
 size_t R11 ; 
 size_t R12 ; 
 size_t R13 ; 
 size_t R14 ; 
 size_t R4 ; 
 int RCBR ; 
 int Rx5 ; 
 int Rx6 ; 
 int Rx7 ; 
 int Rx8 ; 
 int RxN_MASK ; 
 int Rx_OVR ; 
 int SB1 ; 
 int SB2 ; 
 int TCBR ; 
 int Tx5 ; 
 int Tx6 ; 
 int Tx7 ; 
 int Tx8 ; 
 int TxN_MASK ; 
 int X16CLK ; 
 int XCLK_MASK ; 

__attribute__((used)) static void
ip22zilog_convert_to_zs(struct uart_ip22zilog_port *up, unsigned int cflag,
		       unsigned int iflag, int brg)
{

	up->curregs[R10] = NRZ;
	up->curregs[R11] = TCBR | RCBR;

	/* Program BAUD and clock source. */
	up->curregs[R4] &= ~XCLK_MASK;
	up->curregs[R4] |= X16CLK;
	up->curregs[R12] = brg & 0xff;
	up->curregs[R13] = (brg >> 8) & 0xff;
	up->curregs[R14] = BRENAB;

	/* Character size, stop bits, and parity. */
	up->curregs[3] &= ~RxN_MASK;
	up->curregs[5] &= ~TxN_MASK;
	switch (cflag & CSIZE) {
	case CS5:
		up->curregs[3] |= Rx5;
		up->curregs[5] |= Tx5;
		up->parity_mask = 0x1f;
		break;
	case CS6:
		up->curregs[3] |= Rx6;
		up->curregs[5] |= Tx6;
		up->parity_mask = 0x3f;
		break;
	case CS7:
		up->curregs[3] |= Rx7;
		up->curregs[5] |= Tx7;
		up->parity_mask = 0x7f;
		break;
	case CS8:
	default:
		up->curregs[3] |= Rx8;
		up->curregs[5] |= Tx8;
		up->parity_mask = 0xff;
		break;
	}
	up->curregs[4] &= ~0x0c;
	if (cflag & CSTOPB)
		up->curregs[4] |= SB2;
	else
		up->curregs[4] |= SB1;
	if (cflag & PARENB)
		up->curregs[4] |= PAR_ENAB;
	else
		up->curregs[4] &= ~PAR_ENAB;
	if (!(cflag & PARODD))
		up->curregs[4] |= PAR_EVEN;
	else
		up->curregs[4] &= ~PAR_EVEN;

	up->port.read_status_mask = Rx_OVR;
	if (iflag & INPCK)
		up->port.read_status_mask |= CRC_ERR | PAR_ERR;
	if (iflag & (IGNBRK | BRKINT | PARMRK))
		up->port.read_status_mask |= BRK_ABRT;

	up->port.ignore_status_mask = 0;
	if (iflag & IGNPAR)
		up->port.ignore_status_mask |= CRC_ERR | PAR_ERR;
	if (iflag & IGNBRK) {
		up->port.ignore_status_mask |= BRK_ABRT;
		if (iflag & IGNPAR)
			up->port.ignore_status_mask |= Rx_OVR;
	}

	if ((cflag & CREAD) == 0)
		up->port.ignore_status_mask = 0xff;
}