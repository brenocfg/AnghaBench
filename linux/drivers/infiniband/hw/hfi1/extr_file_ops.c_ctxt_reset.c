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
struct send_context {int flags; int /*<<< orphan*/  halt_wait; } ;
struct hfi1_devdata {int flags; int /*<<< orphan*/  event_queue; } ;
struct hfi1_ctxtdata {struct send_context* sc; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOLCK ; 
 int HFI1_FORCED_FREEZE ; 
 int HFI1_FROZEN ; 
 int /*<<< orphan*/  HFI1_RCVCTRL_CTXT_ENB ; 
 int READ_ONCE (int) ; 
 int SCF_FROZEN ; 
 int SCF_HALTED ; 
 int /*<<< orphan*/  SEND_CTXT_HALT_TIMEOUT ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_disable (struct send_context*) ; 
 int sc_enable (struct send_context*) ; 
 int sc_restart (struct send_context*) ; 
 int /*<<< orphan*/  sc_return_credits (struct send_context*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctxt_reset(struct hfi1_ctxtdata *uctxt)
{
	struct send_context *sc;
	struct hfi1_devdata *dd;
	int ret = 0;

	if (!uctxt || !uctxt->dd || !uctxt->sc)
		return -EINVAL;

	/*
	 * There is no protection here. User level has to guarantee that
	 * no one will be writing to the send context while it is being
	 * re-initialized.  If user level breaks that guarantee, it will
	 * break it's own context and no one else's.
	 */
	dd = uctxt->dd;
	sc = uctxt->sc;

	/*
	 * Wait until the interrupt handler has marked the context as
	 * halted or frozen. Report error if we time out.
	 */
	wait_event_interruptible_timeout(
		sc->halt_wait, (sc->flags & SCF_HALTED),
		msecs_to_jiffies(SEND_CTXT_HALT_TIMEOUT));
	if (!(sc->flags & SCF_HALTED))
		return -ENOLCK;

	/*
	 * If the send context was halted due to a Freeze, wait until the
	 * device has been "unfrozen" before resetting the context.
	 */
	if (sc->flags & SCF_FROZEN) {
		wait_event_interruptible_timeout(
			dd->event_queue,
			!(READ_ONCE(dd->flags) & HFI1_FROZEN),
			msecs_to_jiffies(SEND_CTXT_HALT_TIMEOUT));
		if (dd->flags & HFI1_FROZEN)
			return -ENOLCK;

		if (dd->flags & HFI1_FORCED_FREEZE)
			/*
			 * Don't allow context reset if we are into
			 * forced freeze
			 */
			return -ENODEV;

		sc_disable(sc);
		ret = sc_enable(sc);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_ENB, uctxt);
	} else {
		ret = sc_restart(sc);
	}
	if (!ret)
		sc_return_credits(sc);

	return ret;
}