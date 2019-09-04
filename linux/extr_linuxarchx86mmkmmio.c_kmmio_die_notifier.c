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
struct notifier_block {int dummy; } ;
struct die_args {int /*<<< orphan*/  regs; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 unsigned long DIE_DEBUG ; 
 unsigned long DR_STEP ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int post_kmmio_handler (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kmmio_die_notifier(struct notifier_block *nb, unsigned long val, void *args)
{
	struct die_args *arg = args;
	unsigned long* dr6_p = (unsigned long *)ERR_PTR(arg->err);

	if (val == DIE_DEBUG && (*dr6_p & DR_STEP))
		if (post_kmmio_handler(*dr6_p, arg->regs) == 1) {
			/*
			 * Reset the BS bit in dr6 (pointed by args->err) to
			 * denote completion of processing
			 */
			*dr6_p &= ~DR_STEP;
			return NOTIFY_STOP;
		}

	return NOTIFY_DONE;
}