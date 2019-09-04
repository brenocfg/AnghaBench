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
struct pt_regs {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_SMAP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int X86_EFLAGS_AC ; 
 int /*<<< orphan*/  X86_FEATURE_SMAP ; 
 int X86_PF_USER ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static inline bool smap_violation(int error_code, struct pt_regs *regs)
{
	if (!IS_ENABLED(CONFIG_X86_SMAP))
		return false;

	if (!static_cpu_has(X86_FEATURE_SMAP))
		return false;

	if (error_code & X86_PF_USER)
		return false;

	if (!user_mode(regs) && (regs->flags & X86_EFLAGS_AC))
		return false;

	return true;
}