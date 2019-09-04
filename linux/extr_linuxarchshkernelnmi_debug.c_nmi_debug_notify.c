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
struct die_args {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 unsigned long DIE_NMI ; 
 int NMI_DEBOUNCE ; 
 int NMI_DIE ; 
 int NMI_SHOW_REGS ; 
 int NMI_SHOW_STATE ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nmi_actions ; 
 int /*<<< orphan*/  show_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_state () ; 

__attribute__((used)) static int nmi_debug_notify(struct notifier_block *self,
		unsigned long val, void *data)
{
	struct die_args *args = data;

	if (likely(val != DIE_NMI))
		return NOTIFY_DONE;

	if (nmi_actions & NMI_SHOW_STATE)
		show_state();
	if (nmi_actions & NMI_SHOW_REGS)
		show_regs(args->regs);
	if (nmi_actions & NMI_DEBOUNCE)
		mdelay(10);
	if (nmi_actions & NMI_DIE)
		return NOTIFY_BAD;

	return NOTIFY_OK;
}