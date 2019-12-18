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
struct qib_pportdata {int* pkeys; TYPE_1__* dd; int /*<<< orphan*/ * pkeyrefs; } ;
struct qib_devdata {int dummy; } ;
struct qib_ctxtdata {int* pkeys; struct qib_pportdata* ppd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  QIB_IB_CFG_PKEYS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_clean_part_key(struct qib_ctxtdata *rcd,
			       struct qib_devdata *dd)
{
	int i, j, pchanged = 0;
	struct qib_pportdata *ppd = rcd->ppd;

	for (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) {
		if (!rcd->pkeys[i])
			continue;
		for (j = 0; j < ARRAY_SIZE(ppd->pkeys); j++) {
			/* check for match independent of the global bit */
			if ((ppd->pkeys[j] & 0x7fff) !=
			    (rcd->pkeys[i] & 0x7fff))
				continue;
			if (atomic_dec_and_test(&ppd->pkeyrefs[j])) {
				ppd->pkeys[j] = 0;
				pchanged++;
			}
			break;
		}
		rcd->pkeys[i] = 0;
	}
	if (pchanged)
		(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);
}