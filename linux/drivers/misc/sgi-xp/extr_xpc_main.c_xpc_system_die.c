#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct die_args {int /*<<< orphan*/  regs; int /*<<< orphan*/  trapnr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* online_heartbeat ) () ;int /*<<< orphan*/  (* offline_heartbeat ) () ;} ;

/* Variables and functions */
#define  DIE_DEBUG 140 
#define  DIE_GPF 139 
#define  DIE_INIT_MONARCH_ENTER 138 
#define  DIE_INIT_MONARCH_LEAVE 137 
#define  DIE_INT3 136 
#define  DIE_KDEBUG_ENTER 135 
#define  DIE_KDEBUG_LEAVE 134 
#define  DIE_MACHINE_HALT 133 
#define  DIE_MACHINE_RESTART 132 
#define  DIE_MCA_MONARCH_ENTER 131 
#define  DIE_MCA_MONARCH_LEAVE 130 
#define  DIE_OOPS 129 
#define  DIE_TRAP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  X86_TRAP_DF ; 
 int /*<<< orphan*/  X86_TRAP_MF ; 
 int /*<<< orphan*/  X86_TRAP_XF ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_die_deactivate () ; 
 int /*<<< orphan*/  xpc_kdebug_ignore ; 

__attribute__((used)) static int
xpc_system_die(struct notifier_block *nb, unsigned long event, void *_die_args)
{
#ifdef CONFIG_IA64		/* !!! temporary kludge */
	switch (event) {
	case DIE_MACHINE_RESTART:
	case DIE_MACHINE_HALT:
		xpc_die_deactivate();
		break;

	case DIE_KDEBUG_ENTER:
		/* Should lack of heartbeat be ignored by other partitions? */
		if (!xpc_kdebug_ignore)
			break;

		/* fall through */
	case DIE_MCA_MONARCH_ENTER:
	case DIE_INIT_MONARCH_ENTER:
		xpc_arch_ops.offline_heartbeat();
		break;

	case DIE_KDEBUG_LEAVE:
		/* Is lack of heartbeat being ignored by other partitions? */
		if (!xpc_kdebug_ignore)
			break;

		/* fall through */
	case DIE_MCA_MONARCH_LEAVE:
	case DIE_INIT_MONARCH_LEAVE:
		xpc_arch_ops.online_heartbeat();
		break;
	}
#else
	struct die_args *die_args = _die_args;

	switch (event) {
	case DIE_TRAP:
		if (die_args->trapnr == X86_TRAP_DF)
			xpc_die_deactivate();

		if (((die_args->trapnr == X86_TRAP_MF) ||
		     (die_args->trapnr == X86_TRAP_XF)) &&
		    !user_mode(die_args->regs))
			xpc_die_deactivate();

		break;
	case DIE_INT3:
	case DIE_DEBUG:
		break;
	case DIE_OOPS:
	case DIE_GPF:
	default:
		xpc_die_deactivate();
	}
#endif

	return NOTIFY_DONE;
}