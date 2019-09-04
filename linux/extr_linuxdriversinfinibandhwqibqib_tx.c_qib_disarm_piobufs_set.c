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
struct qib_pportdata {size_t port; } ;
struct qib_devdata {unsigned int num_pports; unsigned long* pio_writing; unsigned long* pioavailkernel; int /*<<< orphan*/  pioavail_lock; int /*<<< orphan*/  pport; int /*<<< orphan*/  (* f_sendctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pio_need_disarm; } ;

/* Variables and functions */
 int QIB_MAX_IB_PORTS ; 
 int /*<<< orphan*/  QIB_SENDCTRL_DISARM_BUF (unsigned int) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ find_ctxt (struct qib_devdata*,unsigned int) ; 
 struct qib_pportdata* is_sdma_buf (struct qib_devdata*,unsigned int) ; 
 int /*<<< orphan*/  qib_cancel_sends (struct qib_pportdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,unsigned long*) ; 

void qib_disarm_piobufs_set(struct qib_devdata *dd, unsigned long *mask,
			    unsigned cnt)
{
	struct qib_pportdata *ppd, *pppd[QIB_MAX_IB_PORTS];
	unsigned i;
	unsigned long flags;

	for (i = 0; i < dd->num_pports; i++)
		pppd[i] = NULL;

	for (i = 0; i < cnt; i++) {
		if (!test_bit(i, mask))
			continue;
		/*
		 * If the buffer is owned by the DMA hardware,
		 * reset the DMA engine.
		 */
		ppd = is_sdma_buf(dd, i);
		if (ppd) {
			pppd[ppd->port] = ppd;
			continue;
		}
		/*
		 * If the kernel is writing the buffer or the buffer is
		 * owned by a user process, we can't clear it yet.
		 */
		spin_lock_irqsave(&dd->pioavail_lock, flags);
		if (test_bit(i, dd->pio_writing) ||
		    (!test_bit(i << 1, dd->pioavailkernel) &&
		     find_ctxt(dd, i))) {
			__set_bit(i, dd->pio_need_disarm);
		} else {
			dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(i));
		}
		spin_unlock_irqrestore(&dd->pioavail_lock, flags);
	}

	/* do cancel_sends once per port that had sdma piobufs in error */
	for (i = 0; i < dd->num_pports; i++)
		if (pppd[i])
			qib_cancel_sends(pppd[i]);
}