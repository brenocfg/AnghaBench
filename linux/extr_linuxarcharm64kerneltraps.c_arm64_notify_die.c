#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct siginfo {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int fault_code; scalar_t__ fault_address; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  arm64_force_sig_info (struct siginfo*,char const*,TYPE_2__*) ; 
 TYPE_2__* current ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  die (char const*,struct pt_regs*,int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void arm64_notify_die(const char *str, struct pt_regs *regs,
		      struct siginfo *info, int err)
{
	if (user_mode(regs)) {
		WARN_ON(regs != current_pt_regs());
		current->thread.fault_address = 0;
		current->thread.fault_code = err;
		arm64_force_sig_info(info, str, current);
	} else {
		die(str, regs, err);
	}
}