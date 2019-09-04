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
typedef  scalar_t__ u32 ;
struct qib_pportdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdi; } ;
struct qib_devdata {int unit; TYPE_1__ verbs_dev; int /*<<< orphan*/  list; int /*<<< orphan*/  int_counter; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (scalar_t__) ; 
 int ENOMEM ; 
 struct qib_devdata* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_percpu (int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 scalar_t__ kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ num_online_cpus () ; 
 scalar_t__ qib_cpulist ; 
 scalar_t__ qib_cpulist_count ; 
 int /*<<< orphan*/  qib_dev_list ; 
 int /*<<< orphan*/  qib_devs_lock ; 
 int /*<<< orphan*/  qib_early_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  qib_unit_table ; 
 scalar_t__ rvt_alloc_device (int,int) ; 
 int /*<<< orphan*/  rvt_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_set_ibdev_name (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  u64 ; 

struct qib_devdata *qib_alloc_devdata(struct pci_dev *pdev, size_t extra)
{
	unsigned long flags;
	struct qib_devdata *dd;
	int ret, nports;

	/* extra is * number of ports */
	nports = extra / sizeof(struct qib_pportdata);
	dd = (struct qib_devdata *)rvt_alloc_device(sizeof(*dd) + extra,
						    nports);
	if (!dd)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&dd->list);

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(&qib_devs_lock, flags);

	ret = idr_alloc(&qib_unit_table, dd, 0, 0, GFP_NOWAIT);
	if (ret >= 0) {
		dd->unit = ret;
		list_add(&dd->list, &qib_dev_list);
	}

	spin_unlock_irqrestore(&qib_devs_lock, flags);
	idr_preload_end();

	if (ret < 0) {
		qib_early_err(&pdev->dev,
			      "Could not allocate unit ID: error %d\n", -ret);
		goto bail;
	}
	rvt_set_ibdev_name(&dd->verbs_dev.rdi, "%s%d", "qib", dd->unit);

	dd->int_counter = alloc_percpu(u64);
	if (!dd->int_counter) {
		ret = -ENOMEM;
		qib_early_err(&pdev->dev,
			      "Could not allocate per-cpu int_counter\n");
		goto bail;
	}

	if (!qib_cpulist_count) {
		u32 count = num_online_cpus();

		qib_cpulist = kcalloc(BITS_TO_LONGS(count), sizeof(long),
				      GFP_KERNEL);
		if (qib_cpulist)
			qib_cpulist_count = count;
	}
#ifdef CONFIG_DEBUG_FS
	qib_dbg_ibdev_init(&dd->verbs_dev);
#endif
	return dd;
bail:
	if (!list_empty(&dd->list))
		list_del_init(&dd->list);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
	return ERR_PTR(ret);
}