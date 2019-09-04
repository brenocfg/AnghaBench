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
 int /*<<< orphan*/  NMI_IO_CHECK ; 
 unsigned char NMI_REASON_CLEAR_IOCHK ; 
 unsigned char NMI_REASON_CLEAR_MASK ; 
 int /*<<< orphan*/  NMI_REASON_PORT ; 
 scalar_t__ nmi_handle (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  nmi_panic (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ panic_on_io_nmi ; 
 int /*<<< orphan*/  pr_emerg (char*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
io_check_error(unsigned char reason, struct pt_regs *regs)
{
	unsigned long i;

	/* check to see if anyone registered against these types of errors */
	if (nmi_handle(NMI_IO_CHECK, regs))
		return;

	pr_emerg(
	"NMI: IOCK error (debug interrupt?) for reason %02x on CPU %d.\n",
		 reason, smp_processor_id());
	show_regs(regs);

	if (panic_on_io_nmi) {
		nmi_panic(regs, "NMI IOCK error: Not continuing");

		/*
		 * If we end up here, it means we have received an NMI while
		 * processing panic(). Simply return without delaying and
		 * re-enabling NMIs.
		 */
		return;
	}

	/* Re-enable the IOCK line, wait for a few seconds */
	reason = (reason & NMI_REASON_CLEAR_MASK) | NMI_REASON_CLEAR_IOCHK;
	outb(reason, NMI_REASON_PORT);

	i = 20000;
	while (--i) {
		touch_nmi_watchdog();
		udelay(100);
	}

	reason &= ~NMI_REASON_CLEAR_IOCHK;
	outb(reason, NMI_REASON_PORT);
}