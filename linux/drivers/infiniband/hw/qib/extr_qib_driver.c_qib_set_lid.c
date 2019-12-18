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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct qib_pportdata {unsigned int lid; unsigned int lmc; int /*<<< orphan*/  port; struct qib_devdata* dd; } ;
struct qib_devdata {int /*<<< orphan*/  unit; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_IB_CFG_LIDLMC ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,unsigned int) ; 

int qib_set_lid(struct qib_pportdata *ppd, u32 lid, u8 lmc)
{
	struct qib_devdata *dd = ppd->dd;

	ppd->lid = lid;
	ppd->lmc = lmc;

	dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LIDLMC,
			 lid | (~((1U << lmc) - 1)) << 16);

	qib_devinfo(dd->pcidev, "IB%u:%u got a lid: 0x%x\n",
		    dd->unit, ppd->port, lid);

	return 0;
}