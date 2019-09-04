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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  spd ;
typedef  int /*<<< orphan*/  reg_shift ;
typedef  int /*<<< orphan*/  reg_offset ;
typedef  int /*<<< orphan*/  clk ;

/* Variables and functions */
 int UART_DLL ; 
 int UART_DLM ; 
 int UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_LCR ; 
 int UART_LCR_DLAB ; 
 int UART_LCR_WLEN8 ; 
 int UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int dt_get_virtual_reg (void*,void**,int) ; 
 int getprop (void*,char*,void*,int) ; 
 int /*<<< orphan*/  out_8 (unsigned char*,int) ; 

__attribute__((used)) static int virtex_ns16550_console_init(void *devp)
{
	unsigned char *reg_base;
	u32 reg_shift, reg_offset, clk, spd;
	u16 divisor;
	int n;

	if (dt_get_virtual_reg(devp, (void **)&reg_base, 1) < 1)
		return -1;

	n = getprop(devp, "reg-offset", &reg_offset, sizeof(reg_offset));
	if (n == sizeof(reg_offset))
		reg_base += reg_offset;

	n = getprop(devp, "reg-shift", &reg_shift, sizeof(reg_shift));
	if (n != sizeof(reg_shift))
		reg_shift = 0;

	n = getprop(devp, "current-speed", (void *)&spd, sizeof(spd));
	if (n != sizeof(spd))
		spd = 9600;

	/* should there be a default clock rate?*/
	n = getprop(devp, "clock-frequency", (void *)&clk, sizeof(clk));
	if (n != sizeof(clk))
		return -1;

	divisor = clk / (16 * spd);

	/* Access baud rate */
	out_8(reg_base + (UART_LCR << reg_shift), UART_LCR_DLAB);

	/* Baud rate based on input clock */
	out_8(reg_base + (UART_DLL << reg_shift), divisor & 0xFF);
	out_8(reg_base + (UART_DLM << reg_shift), divisor >> 8);

	/* 8 data, 1 stop, no parity */
	out_8(reg_base + (UART_LCR << reg_shift), UART_LCR_WLEN8);

	/* RTS/DTR */
	out_8(reg_base + (UART_MCR << reg_shift), UART_MCR_RTS | UART_MCR_DTR);

	/* Clear transmitter and receiver */
	out_8(reg_base + (UART_FCR << reg_shift),
				UART_FCR_CLEAR_XMIT | UART_FCR_CLEAR_RCVR);
	return 0;
}