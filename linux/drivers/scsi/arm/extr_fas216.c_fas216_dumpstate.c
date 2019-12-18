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
typedef  int /*<<< orphan*/  FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CFIS ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_CNTL1 ; 
 int /*<<< orphan*/  REG_CNTL2 ; 
 int /*<<< orphan*/  REG_CNTL3 ; 
 int /*<<< orphan*/  REG_CTCH ; 
 int /*<<< orphan*/  REG_CTCL ; 
 int /*<<< orphan*/  REG_CTCM ; 
 int /*<<< orphan*/  REG_INST ; 
 int /*<<< orphan*/  REG_IS ; 
 int /*<<< orphan*/  REG_STAT ; 
 unsigned char fas216_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned char,unsigned char,unsigned char,unsigned char,...) ; 

__attribute__((used)) static void fas216_dumpstate(FAS216_Info *info)
{
	unsigned char is, stat, inst;

	is   = fas216_readb(info, REG_IS);
	stat = fas216_readb(info, REG_STAT);
	inst = fas216_readb(info, REG_INST);
	
	printk("FAS216: CTCL=%02X CTCM=%02X CMD=%02X STAT=%02X"
	       " INST=%02X IS=%02X CFIS=%02X",
		fas216_readb(info, REG_CTCL),
		fas216_readb(info, REG_CTCM),
		fas216_readb(info, REG_CMD),  stat, inst, is,
		fas216_readb(info, REG_CFIS));
	printk(" CNTL1=%02X CNTL2=%02X CNTL3=%02X CTCH=%02X\n",
		fas216_readb(info, REG_CNTL1),
		fas216_readb(info, REG_CNTL2),
		fas216_readb(info, REG_CNTL3),
		fas216_readb(info, REG_CTCH));
}