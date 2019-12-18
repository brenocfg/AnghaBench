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

/* Variables and functions */
 int SE2CLK ; 
 int SE2CS ; 
 int SE2DO ; 
 scalar_t__ TUL_NVRAM ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void initio_se2_instr(unsigned long base, u8 instr)
{
	int i;
	u8 b;

	outb(SE2CS | SE2DO, base + TUL_NVRAM);		/* cs+start bit */
	udelay(30);
	outb(SE2CS | SE2CLK | SE2DO, base + TUL_NVRAM);	/* +CLK */
	udelay(30);

	for (i = 0; i < 8; i++) {
		if (instr & 0x80)
			b = SE2CS | SE2DO;		/* -CLK+dataBit */
		else
			b = SE2CS;			/* -CLK */
		outb(b, base + TUL_NVRAM);
		udelay(30);
		outb(b | SE2CLK, base + TUL_NVRAM);	/* +CLK */
		udelay(30);
		instr <<= 1;
	}
	outb(SE2CS, base + TUL_NVRAM);			/* -CLK */
	udelay(30);
}