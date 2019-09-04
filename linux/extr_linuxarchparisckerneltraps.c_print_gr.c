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
struct pt_regs {int /*<<< orphan*/ * gr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTREGS (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFMT ; 
 int /*<<< orphan*/  print_tainted () ; 
 int /*<<< orphan*/  printbinary (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,char*,...) ; 

__attribute__((used)) static void print_gr(char *level, struct pt_regs *regs)
{
	int i;
	char buf[64];

	printk("%s\n", level);
	printk("%s     YZrvWESTHLNXBCVMcbcbcbcbOGFRQPDI\n", level);
	printbinary(buf, regs->gr[0], 32);
	printk("%sPSW: %s %s\n", level, buf, print_tainted());

	for (i = 0; i < 32; i += 4)
		PRINTREGS(level, regs->gr, "r", RFMT, i);
}