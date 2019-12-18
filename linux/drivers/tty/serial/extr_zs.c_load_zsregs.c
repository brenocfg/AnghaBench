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
struct zs_port {int dummy; } ;

/* Variables and functions */
 int BRENABL ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R11 ; 
 int /*<<< orphan*/  R12 ; 
 int /*<<< orphan*/  R13 ; 
 int /*<<< orphan*/  R14 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R9 ; 
 int RxENABLE ; 
 int TxENAB ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zs_line_drain (struct zs_port*,int) ; 

__attribute__((used)) static void load_zsregs(struct zs_port *zport, u8 *regs, int irq)
{
	/* Let the current transmission finish.  */
	zs_line_drain(zport, irq);
	/* Load 'em up.  */
	write_zsreg(zport, R3, regs[3] & ~RxENABLE);
	write_zsreg(zport, R5, regs[5] & ~TxENAB);
	write_zsreg(zport, R4, regs[4]);
	write_zsreg(zport, R9, regs[9]);
	write_zsreg(zport, R1, regs[1]);
	write_zsreg(zport, R2, regs[2]);
	write_zsreg(zport, R10, regs[10]);
	write_zsreg(zport, R14, regs[14] & ~BRENABL);
	write_zsreg(zport, R11, regs[11]);
	write_zsreg(zport, R12, regs[12]);
	write_zsreg(zport, R13, regs[13]);
	write_zsreg(zport, R14, regs[14]);
	write_zsreg(zport, R15, regs[15]);
	if (regs[3] & RxENABLE)
		write_zsreg(zport, R3, regs[3]);
	if (regs[5] & TxENAB)
		write_zsreg(zport, R5, regs[5]);
	return;
}