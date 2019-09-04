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
struct undef_hook {scalar_t__ instr_mask; } ;
struct insn_emulation_ops {int /*<<< orphan*/  name; struct undef_hook* hooks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_undef_hook (struct undef_hook*) ; 

__attribute__((used)) static void register_emulation_hooks(struct insn_emulation_ops *ops)
{
	struct undef_hook *hook;

	BUG_ON(!ops->hooks);

	for (hook = ops->hooks; hook->instr_mask; hook++)
		register_undef_hook(hook);

	pr_notice("Registered %s emulation handler\n", ops->name);
}