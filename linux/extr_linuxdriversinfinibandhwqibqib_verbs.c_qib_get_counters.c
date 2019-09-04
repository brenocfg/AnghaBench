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
struct qib_verbs_counters {scalar_t__ vl15_dropped; scalar_t__ excessive_buffer_overrun_errors; scalar_t__ local_link_integrity_errors; scalar_t__ port_rcv_packets; scalar_t__ port_xmit_packets; scalar_t__ port_rcv_data; scalar_t__ port_xmit_data; scalar_t__ port_xmit_discards; scalar_t__ port_rcv_remphys_errors; scalar_t__ port_rcv_errors; scalar_t__ link_downed_counter; scalar_t__ link_error_recovery_counter; scalar_t__ symbol_error_counter; } ;
struct qib_pportdata {TYPE_1__* dd; } ;
struct TYPE_2__ {int flags; scalar_t__ (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QIBPORTCNTR_BADFORMAT ; 
 int /*<<< orphan*/  QIBPORTCNTR_ERRICRC ; 
 int /*<<< orphan*/  QIBPORTCNTR_ERRLINK ; 
 int /*<<< orphan*/  QIBPORTCNTR_ERRLPCRC ; 
 int /*<<< orphan*/  QIBPORTCNTR_ERRVCRC ; 
 int /*<<< orphan*/  QIBPORTCNTR_ERR_RLEN ; 
 int /*<<< orphan*/  QIBPORTCNTR_EXCESSBUFOVFL ; 
 int /*<<< orphan*/  QIBPORTCNTR_IBLINKDOWN ; 
 int /*<<< orphan*/  QIBPORTCNTR_IBLINKERRRECOV ; 
 int /*<<< orphan*/  QIBPORTCNTR_IBSYMBOLERR ; 
 int /*<<< orphan*/  QIBPORTCNTR_INVALIDRLEN ; 
 int /*<<< orphan*/  QIBPORTCNTR_LLI ; 
 int /*<<< orphan*/  QIBPORTCNTR_PKTRCV ; 
 int /*<<< orphan*/  QIBPORTCNTR_PKTSEND ; 
 int /*<<< orphan*/  QIBPORTCNTR_RCVEBP ; 
 int /*<<< orphan*/  QIBPORTCNTR_RCVOVFL ; 
 int /*<<< orphan*/  QIBPORTCNTR_RXDROPPKT ; 
 int /*<<< orphan*/  QIBPORTCNTR_RXLOCALPHYERR ; 
 int /*<<< orphan*/  QIBPORTCNTR_RXVLERR ; 
 int /*<<< orphan*/  QIBPORTCNTR_UNSUPVL ; 
 int /*<<< orphan*/  QIBPORTCNTR_VL15PKTDROP ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDRCV ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDSEND ; 
 int QIB_PRESENT ; 
 scalar_t__ stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub10 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub11 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub12 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub13 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub14 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub15 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub16 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub17 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub18 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub19 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub20 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub21 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub22 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub23 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub8 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub9 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

int qib_get_counters(struct qib_pportdata *ppd,
		     struct qib_verbs_counters *cntrs)
{
	int ret;

	if (!(ppd->dd->flags & QIB_PRESENT)) {
		/* no hardware, freeze, etc. */
		ret = -EINVAL;
		goto bail;
	}
	cntrs->symbol_error_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBSYMBOLERR);
	cntrs->link_error_recovery_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBLINKERRRECOV);
	/*
	 * The link downed counter counts when the other side downs the
	 * connection.  We add in the number of times we downed the link
	 * due to local link integrity errors to compensate.
	 */
	cntrs->link_downed_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBLINKDOWN);
	cntrs->port_rcv_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXDROPPKT) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RCVOVFL) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERR_RLEN) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_INVALIDRLEN) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRLINK) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRICRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRVCRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRLPCRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_BADFORMAT);
	cntrs->port_rcv_errors +=
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXLOCALPHYERR);
	cntrs->port_rcv_errors +=
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXVLERR);
	cntrs->port_rcv_remphys_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RCVEBP);
	cntrs->port_xmit_discards =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_UNSUPVL);
	cntrs->port_xmit_data = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_WORDSEND);
	cntrs->port_rcv_data = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_WORDRCV);
	cntrs->port_xmit_packets = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_PKTSEND);
	cntrs->port_rcv_packets = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_PKTRCV);
	cntrs->local_link_integrity_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_LLI);
	cntrs->excessive_buffer_overrun_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_EXCESSBUFOVFL);
	cntrs->vl15_dropped =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_VL15PKTDROP);

	ret = 0;

bail:
	return ret;
}