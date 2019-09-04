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

/* Variables and functions */
 int CPC0_CR0_U0EC ; 
 int CPC0_CR0_U1EC ; 
 int CPC0_CR0_UDIV (int) ; 
 int CPC0_SYS0_BYPASS ; 
 int CPC0_SYS0_EPDV (int) ; 
 int CPC0_SYS0_EXTSL ; 
 unsigned int CPC0_SYS0_FBDV (int) ; 
 unsigned int CPC0_SYS0_FWDVA (int) ; 
 unsigned int CPC0_SYS0_FWDVB (int) ; 
 int CPC0_SYS0_OPDV (int) ; 
 int /*<<< orphan*/  DCRN_CPC0_CR0 ; 
 int /*<<< orphan*/  DCRN_CPC0_SYS0 ; 
 int /*<<< orphan*/  dt_fixup_clock (char*,int) ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int,int,int /*<<< orphan*/ ) ; 
 int mfdcr (int /*<<< orphan*/ ) ; 
 int mfpvr () ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int) ; 

void ibm440gp_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk)
{
	u32 sys0 = mfdcr(DCRN_CPC0_SYS0);
	u32 cr0 = mfdcr(DCRN_CPC0_CR0);
	u32 cpu, plb, opb, ebc, tb, uart0, uart1, m;
	u32 opdv = CPC0_SYS0_OPDV(sys0);
	u32 epdv = CPC0_SYS0_EPDV(sys0);

	if (sys0 & CPC0_SYS0_BYPASS) {
		/* Bypass system PLL */
		cpu = plb = sys_clk;
	} else {
		if (sys0 & CPC0_SYS0_EXTSL)
			/* PerClk */
			m = CPC0_SYS0_FWDVB(sys0) * opdv * epdv;
		else
			/* CPU clock */
			m = CPC0_SYS0_FBDV(sys0) * CPC0_SYS0_FWDVA(sys0);
		cpu = sys_clk * m / CPC0_SYS0_FWDVA(sys0);
		plb = sys_clk * m / CPC0_SYS0_FWDVB(sys0);
	}

	opb = plb / opdv;
	ebc = opb / epdv;

	/* FIXME: Check if this is for all 440GP, or just Ebony */
	if ((mfpvr() & 0xf0000fff) == 0x40000440)
		/* Rev. B 440GP, use external system clock */
		tb = sys_clk;
	else
		/* Rev. C 440GP, errata force us to use internal clock */
		tb = cpu;

	if (cr0 & CPC0_CR0_U0EC)
		/* External UART clock */
		uart0 = ser_clk;
	else
		/* Internal UART clock */
		uart0 = plb / CPC0_CR0_UDIV(cr0);

	if (cr0 & CPC0_CR0_U1EC)
		/* External UART clock */
		uart1 = ser_clk;
	else
		/* Internal UART clock */
		uart1 = plb / CPC0_CR0_UDIV(cr0);

	printf("PPC440GP: SysClk = %dMHz (%x)\n\r",
	       (sys_clk + 500000) / 1000000, sys_clk);

	dt_fixup_cpu_clocks(cpu, tb, 0);

	dt_fixup_clock("/plb", plb);
	dt_fixup_clock("/plb/opb", opb);
	dt_fixup_clock("/plb/opb/ebc", ebc);
	dt_fixup_clock("/plb/opb/serial@40000200", uart0);
	dt_fixup_clock("/plb/opb/serial@40000300", uart1);
}