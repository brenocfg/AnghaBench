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
typedef  int u16 ;
struct qib_pportdata {int* pkeys; TYPE_1__* dd; int /*<<< orphan*/ * pkeyrefs; } ;
struct qib_ctxtdata {int* pkeys; struct qib_pportdata* ppd; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int QIB_DEFAULT_P_KEY ; 
 int /*<<< orphan*/  QIB_IB_CFG_PKEYS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_set_part_key(struct qib_ctxtdata *rcd, u16 key)
{
	struct qib_pportdata *ppd = rcd->ppd;
	int i, pidx = -1;
	bool any = false;
	u16 lkey = key & 0x7FFF;

	if (lkey == (QIB_DEFAULT_P_KEY & 0x7FFF))
		/* nothing to do; this key always valid */
		return 0;

	if (!lkey)
		return -EINVAL;

	/*
	 * Set the full membership bit, because it has to be
	 * set in the register or the packet, and it seems
	 * cleaner to set in the register than to force all
	 * callers to set it.
	 */
	key |= 0x8000;

	for (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) {
		if (!rcd->pkeys[i] && pidx == -1)
			pidx = i;
		if (rcd->pkeys[i] == key)
			return -EEXIST;
	}
	if (pidx == -1)
		return -EBUSY;
	for (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) {
		if (!ppd->pkeys[i]) {
			any = true;
			continue;
		}
		if (ppd->pkeys[i] == key) {
			atomic_t *pkrefs = &ppd->pkeyrefs[i];

			if (atomic_inc_return(pkrefs) > 1) {
				rcd->pkeys[pidx] = key;
				return 0;
			}
			/*
			 * lost race, decrement count, catch below
			 */
			atomic_dec(pkrefs);
			any = true;
		}
		if ((ppd->pkeys[i] & 0x7FFF) == lkey)
			/*
			 * It makes no sense to have both the limited and
			 * full membership PKEY set at the same time since
			 * the unlimited one will disable the limited one.
			 */
			return -EEXIST;
	}
	if (!any)
		return -EBUSY;
	for (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) {
		if (!ppd->pkeys[i] &&
		    atomic_inc_return(&ppd->pkeyrefs[i]) == 1) {
			rcd->pkeys[pidx] = key;
			ppd->pkeys[i] = key;
			(void) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);
			return 0;
		}
	}
	return -EBUSY;
}