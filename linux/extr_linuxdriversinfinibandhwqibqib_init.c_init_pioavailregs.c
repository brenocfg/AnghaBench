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
typedef  int /*<<< orphan*/  u64 ;
struct qib_devdata {int pioavregs; int num_pports; char* freezemsg; scalar_t__ freezelen; scalar_t__ pioavailregs_dma; TYPE_2__* pport; int /*<<< orphan*/ * devstatusp; int /*<<< orphan*/  pioavailregs_phys; TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * statusp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int L1_CACHE_BYTES ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 

__attribute__((used)) static int init_pioavailregs(struct qib_devdata *dd)
{
	int ret, pidx;
	u64 *status_page;

	dd->pioavailregs_dma = dma_alloc_coherent(
		&dd->pcidev->dev, PAGE_SIZE, &dd->pioavailregs_phys,
		GFP_KERNEL);
	if (!dd->pioavailregs_dma) {
		qib_dev_err(dd,
			"failed to allocate PIOavail reg area in memory\n");
		ret = -ENOMEM;
		goto done;
	}

	/*
	 * We really want L2 cache aligned, but for current CPUs of
	 * interest, they are the same.
	 */
	status_page = (u64 *)
		((char *) dd->pioavailregs_dma +
		 ((2 * L1_CACHE_BYTES +
		   dd->pioavregs * sizeof(u64)) & ~L1_CACHE_BYTES));
	/* device status comes first, for backwards compatibility */
	dd->devstatusp = status_page;
	*status_page++ = 0;
	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		dd->pport[pidx].statusp = status_page;
		*status_page++ = 0;
	}

	/*
	 * Setup buffer to hold freeze and other messages, accessible to
	 * apps, following statusp.  This is per-unit, not per port.
	 */
	dd->freezemsg = (char *) status_page;
	*dd->freezemsg = 0;
	/* length of msg buffer is "whatever is left" */
	ret = (char *) status_page - (char *) dd->pioavailregs_dma;
	dd->freezelen = PAGE_SIZE - ret;

	ret = 0;

done:
	return ret;
}