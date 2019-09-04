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
typedef  int /*<<< orphan*/  wq_name ;
struct qib_pportdata {int /*<<< orphan*/ * qib_wq; } ;
struct qib_devdata {int num_pports; int unit; struct qib_pportdata* pport; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/ * alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static int qib_create_workqueues(struct qib_devdata *dd)
{
	int pidx;
	struct qib_pportdata *ppd;

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (!ppd->qib_wq) {
			char wq_name[8]; /* 3 + 2 + 1 + 1 + 1 */

			snprintf(wq_name, sizeof(wq_name), "qib%d_%d",
				dd->unit, pidx);
			ppd->qib_wq = alloc_ordered_workqueue(wq_name,
							      WQ_MEM_RECLAIM);
			if (!ppd->qib_wq)
				goto wq_error;
		}
	}
	return 0;
wq_error:
	pr_err("create_singlethread_workqueue failed for port %d\n",
		pidx + 1);
	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (ppd->qib_wq) {
			destroy_workqueue(ppd->qib_wq);
			ppd->qib_wq = NULL;
		}
	}
	return -ENOMEM;
}