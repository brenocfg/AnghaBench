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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  CONFIG_NUMA ; 
 int /*<<< orphan*/  CONFIG_PREEMPT ; 
 int /*<<< orphan*/  CONFIG_SMP ; 
 int /*<<< orphan*/  DIE_OOPS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTIFY_STOP ; 
 char* NR_CPUS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 scalar_t__ debug_pagealloc_enabled () ; 
 int /*<<< orphan*/  die_counter ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char const*,struct pt_regs*,long,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

__attribute__((used)) static int __die(const char *str, struct pt_regs *regs, long err)
{
	printk("Oops: %s, sig: %ld [#%d]\n", str, err, ++die_counter);

	if (IS_ENABLED(CONFIG_CPU_LITTLE_ENDIAN))
		printk("LE ");
	else
		printk("BE ");

	if (IS_ENABLED(CONFIG_PREEMPT))
		pr_cont("PREEMPT ");

	if (IS_ENABLED(CONFIG_SMP))
		pr_cont("SMP NR_CPUS=%d ", NR_CPUS);

	if (debug_pagealloc_enabled())
		pr_cont("DEBUG_PAGEALLOC ");

	if (IS_ENABLED(CONFIG_NUMA))
		pr_cont("NUMA ");

	pr_cont("%s\n", ppc_md.name ? ppc_md.name : "");

	if (notify_die(DIE_OOPS, str, regs, err, 255, SIGSEGV) == NOTIFY_STOP)
		return 1;

	print_modules();
	show_regs(regs);

	return 0;
}