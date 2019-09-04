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
struct die_args {int /*<<< orphan*/  signr; struct pt_regs* regs; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ kgdb_handle_exception (int,int /*<<< orphan*/ ,unsigned long,struct pt_regs*) ; 

__attribute__((used)) static int __kgdb_notify(struct die_args *args, unsigned long cmd)
{
	struct pt_regs *regs = args->regs;

	if (kgdb_handle_exception(1, args->signr, cmd, regs))
		return NOTIFY_DONE;
	return NOTIFY_STOP;
}