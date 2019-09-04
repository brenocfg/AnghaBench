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
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (long) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,long) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void die(const char *str, struct pt_regs *fp, long err)
{
	console_verbose();
	spin_lock_irq(&die_lock);
	pr_warn("Oops: %s, sig: %ld\n", str, err);
	show_regs(fp);
	spin_unlock_irq(&die_lock);
	/* do_exit() should take care of panic'ing from an interrupt
	 * context so we don't handle it here
	 */
	do_exit(err);
}