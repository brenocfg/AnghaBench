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
struct pt_regs {int /*<<< orphan*/  int_parm_long; } ;
struct perf_sf_sde_regs {scalar_t__ in_guest; } ;

/* Variables and functions */
 unsigned long PERF_RECORD_MISC_GUEST_KERNEL ; 
 unsigned long PERF_RECORD_MISC_GUEST_USER ; 
 unsigned long PERF_RECORD_MISC_KERNEL ; 
 unsigned long PERF_RECORD_MISC_USER ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static unsigned long perf_misc_flags_sf(struct pt_regs *regs)
{
	struct perf_sf_sde_regs *sde_regs;
	unsigned long flags;

	sde_regs = (struct perf_sf_sde_regs *) &regs->int_parm_long;
	if (sde_regs->in_guest)
		flags = user_mode(regs) ? PERF_RECORD_MISC_GUEST_USER
					: PERF_RECORD_MISC_GUEST_KERNEL;
	else
		flags = user_mode(regs) ? PERF_RECORD_MISC_USER
					: PERF_RECORD_MISC_KERNEL;
	return flags;
}