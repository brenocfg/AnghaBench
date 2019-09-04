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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _send_sig (int,int,unsigned long) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void _exception(int signo, struct pt_regs *regs, int code, unsigned long addr)
{
	if (!user_mode(regs))
		die("Exception in kernel mode", regs, signo);

	_send_sig(signo, code, addr);
}