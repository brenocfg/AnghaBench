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
typedef  scalar_t__ u64 ;
struct qib_pportdata {int dummy; } ;
struct qib_devdata {scalar_t__ rcvhdrentsize; scalar_t__ rcvhdrsize; scalar_t__ rcvhdrcnt; scalar_t__ pioavailregs_phys; int piobcnt2k; int piobcnt4k; scalar_t__ control; int num_pports; int flags; struct qib_pportdata* pport; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_VL15_BUFS ; 
 int QIB_HAS_QSFP ; 
 scalar_t__ QLOGIC_IB_C_SDMAFETCHPRIOEN ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_ENAB1 ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_KERN ; 
 int /*<<< orphan*/  kr_control ; 
 int /*<<< orphan*/  kr_rcvhdrcnt ; 
 int /*<<< orphan*/  kr_rcvhdrentsize ; 
 int /*<<< orphan*/  kr_rcvhdrsize ; 
 int /*<<< orphan*/  kr_sendpioavailaddr ; 
 int /*<<< orphan*/  krp_senddmaprioritythld ; 
 int /*<<< orphan*/  qib_7322_txchk_change (struct qib_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,unsigned long,unsigned long long) ; 
 int /*<<< orphan*/  qib_init_7322_qsfp (struct qib_pportdata*) ; 
 scalar_t__ qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_register_observer (struct qib_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int sdma_fetch_prio ; 
 int /*<<< orphan*/  sendctrl_0_observer ; 
 int /*<<< orphan*/  sendctrl_1_observer ; 
 int /*<<< orphan*/  set_no_qsfp_atten (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_late_7322_initreg(struct qib_devdata *dd)
{
	int ret = 0, n;
	u64 val;

	qib_write_kreg(dd, kr_rcvhdrentsize, dd->rcvhdrentsize);
	qib_write_kreg(dd, kr_rcvhdrsize, dd->rcvhdrsize);
	qib_write_kreg(dd, kr_rcvhdrcnt, dd->rcvhdrcnt);
	qib_write_kreg(dd, kr_sendpioavailaddr, dd->pioavailregs_phys);
	val = qib_read_kreg64(dd, kr_sendpioavailaddr);
	if (val != dd->pioavailregs_phys) {
		qib_dev_err(dd,
			"Catastrophic software error, SendPIOAvailAddr written as %lx, read back as %llx\n",
			(unsigned long) dd->pioavailregs_phys,
			(unsigned long long) val);
		ret = -EINVAL;
	}

	n = dd->piobcnt2k + dd->piobcnt4k + NUM_VL15_BUFS;
	qib_7322_txchk_change(dd, 0, n, TXCHK_CHG_TYPE_KERN, NULL);
	/* driver sends get pkey, lid, etc. checking also, to catch bugs */
	qib_7322_txchk_change(dd, 0, n, TXCHK_CHG_TYPE_ENAB1, NULL);

	qib_register_observer(dd, &sendctrl_0_observer);
	qib_register_observer(dd, &sendctrl_1_observer);

	dd->control &= ~QLOGIC_IB_C_SDMAFETCHPRIOEN;
	qib_write_kreg(dd, kr_control, dd->control);
	/*
	 * Set SendDmaFetchPriority and init Tx params, including
	 * QSFP handler on boards that have QSFP.
	 * First set our default attenuation entry for cables that
	 * don't have valid attenuation.
	 */
	set_no_qsfp_atten(dd, 0);
	for (n = 0; n < dd->num_pports; ++n) {
		struct qib_pportdata *ppd = dd->pport + n;

		qib_write_kreg_port(ppd, krp_senddmaprioritythld,
				    sdma_fetch_prio & 0xf);
		/* Initialize qsfp if present on board. */
		if (dd->flags & QIB_HAS_QSFP)
			qib_init_7322_qsfp(ppd);
	}
	dd->control |= QLOGIC_IB_C_SDMAFETCHPRIOEN;
	qib_write_kreg(dd, kr_control, dd->control);

	return ret;
}