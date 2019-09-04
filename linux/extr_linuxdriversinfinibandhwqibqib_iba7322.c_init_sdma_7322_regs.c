#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_4__ {unsigned int first_sendbuf; unsigned int last_sendbuf; } ;
struct qib_pportdata {unsigned long long sdma_descq_phys; unsigned long long sdma_head_phys; int port; TYPE_2__ sdma_state; struct qib_devdata* dd; } ;
struct qib_devdata {int num_pports; int piobcnt2k; int piobcnt4k; TYPE_1__* cspec; } ;
struct TYPE_3__ {int sdmabufcnt; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  krp_senddmabase ; 
 int /*<<< orphan*/  krp_senddmabufmask0 ; 
 int /*<<< orphan*/  krp_senddmabufmask1 ; 
 int /*<<< orphan*/  krp_senddmabufmask2 ; 
 int /*<<< orphan*/  krp_senddmadesccnt ; 
 int /*<<< orphan*/  krp_senddmaheadaddr ; 
 int /*<<< orphan*/  krp_senddmareloadcnt ; 
 int /*<<< orphan*/  qib_sdma_7322_setlengen (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_update_7322_tail (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long sdma_idle_cnt ; 

__attribute__((used)) static int init_sdma_7322_regs(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;
	unsigned lastbuf, erstbuf;
	u64 senddmabufmask[3] = { 0 };
	int n, ret = 0;

	qib_write_kreg_port(ppd, krp_senddmabase, ppd->sdma_descq_phys);
	qib_sdma_7322_setlengen(ppd);
	qib_sdma_update_7322_tail(ppd, 0); /* Set SendDmaTail */
	qib_write_kreg_port(ppd, krp_senddmareloadcnt, sdma_idle_cnt);
	qib_write_kreg_port(ppd, krp_senddmadesccnt, 0);
	qib_write_kreg_port(ppd, krp_senddmaheadaddr, ppd->sdma_head_phys);

	if (dd->num_pports)
		n = dd->cspec->sdmabufcnt / dd->num_pports; /* no remainder */
	else
		n = dd->cspec->sdmabufcnt; /* failsafe for init */
	erstbuf = (dd->piobcnt2k + dd->piobcnt4k) -
		((dd->num_pports == 1 || ppd->port == 2) ? n :
		dd->cspec->sdmabufcnt);
	lastbuf = erstbuf + n;

	ppd->sdma_state.first_sendbuf = erstbuf;
	ppd->sdma_state.last_sendbuf = lastbuf;
	for (; erstbuf < lastbuf; ++erstbuf) {
		unsigned word = erstbuf / BITS_PER_LONG;
		unsigned bit = erstbuf & (BITS_PER_LONG - 1);

		BUG_ON(word >= 3);
		senddmabufmask[word] |= 1ULL << bit;
	}
	qib_write_kreg_port(ppd, krp_senddmabufmask0, senddmabufmask[0]);
	qib_write_kreg_port(ppd, krp_senddmabufmask1, senddmabufmask[1]);
	qib_write_kreg_port(ppd, krp_senddmabufmask2, senddmabufmask[2]);
	return ret;
}