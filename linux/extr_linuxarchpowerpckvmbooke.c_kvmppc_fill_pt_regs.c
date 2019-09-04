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
typedef  void* ulong ;
struct pt_regs {void* link; void* msr; void* nip; void** gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvmppc_fill_pt_regs(struct pt_regs *regs)
{
	ulong r1, ip, msr, lr;

	asm("mr %0, 1" : "=r"(r1));
	asm("mflr %0" : "=r"(lr));
	asm("mfmsr %0" : "=r"(msr));
	asm("bl 1f; 1: mflr %0" : "=r"(ip));

	memset(regs, 0, sizeof(*regs));
	regs->gpr[1] = r1;
	regs->nip = ip;
	regs->msr = msr;
	regs->link = lr;
}