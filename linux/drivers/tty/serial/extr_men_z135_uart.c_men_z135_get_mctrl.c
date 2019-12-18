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
typedef  int u8 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int MEN_Z135_MSR_CTS ; 
 int MEN_Z135_MSR_DCD ; 
 int MEN_Z135_MSR_DSR ; 
 int MEN_Z135_MSR_RI ; 
 scalar_t__ MEN_Z135_STAT_REG ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 int ioread8 (scalar_t__) ; 

__attribute__((used)) static unsigned int men_z135_get_mctrl(struct uart_port *port)
{
	unsigned int mctrl = 0;
	u8 msr;

	msr = ioread8(port->membase + MEN_Z135_STAT_REG + 1);

	if (msr & MEN_Z135_MSR_CTS)
		mctrl |= TIOCM_CTS;
	if (msr & MEN_Z135_MSR_DSR)
		mctrl |= TIOCM_DSR;
	if (msr & MEN_Z135_MSR_RI)
		mctrl |= TIOCM_RI;
	if (msr & MEN_Z135_MSR_DCD)
		mctrl |= TIOCM_CAR;

	return mctrl;
}