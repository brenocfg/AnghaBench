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
struct qib_devdata {int num_pports; scalar_t__ pport; int /*<<< orphan*/  (* f_quiet_serdes ) (scalar_t__) ;int /*<<< orphan*/  flags; } ;
struct pci_device_id {int device; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct qib_devdata* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct qib_devdata*) ; 
#define  PCI_DEVICE_ID_QLOGIC_IB_6120 130 
#define  PCI_DEVICE_ID_QLOGIC_IB_7220 129 
#define  PCI_DEVICE_ID_QLOGIC_IB_7322 128 
 int PTR_ERR (struct qib_devdata*) ; 
 int /*<<< orphan*/  QIB_INITTED ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wq ; 
 int qib_create_workqueues (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int) ; 
 int qib_device_create (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_device_remove (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_early_err (int /*<<< orphan*/ *,char*,int) ; 
 int qib_enable_wc (struct qib_devdata*) ; 
 int qib_init (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 struct qib_devdata* qib_init_iba6120_funcs (struct pci_dev*,struct pci_device_id const*) ; 
 struct qib_devdata* qib_init_iba7220_funcs (struct pci_dev*,struct pci_device_id const*) ; 
 struct qib_devdata* qib_init_iba7322_funcs (struct pci_dev*,struct pci_device_id const*) ; 
 scalar_t__ qib_mini_init ; 
 int qib_pcie_init (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  qib_postinit_cleanup (struct qib_devdata*) ; 
 int qib_register_ib_device (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_stop_timers (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_unregister_ib_device (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_verify_pioperf (struct qib_devdata*) ; 
 int qibfs_add (struct qib_devdata*) ; 
 int /*<<< orphan*/  qibfs_remove (struct qib_devdata*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static int qib_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int ret, j, pidx, initfail;
	struct qib_devdata *dd = NULL;

	ret = qib_pcie_init(pdev, ent);
	if (ret)
		goto bail;

	/*
	 * Do device-specific initialiation, function table setup, dd
	 * allocation, etc.
	 */
	switch (ent->device) {
	case PCI_DEVICE_ID_QLOGIC_IB_6120:
#ifdef CONFIG_PCI_MSI
		dd = qib_init_iba6120_funcs(pdev, ent);
#else
		qib_early_err(&pdev->dev,
			"Intel PCIE device 0x%x cannot work if CONFIG_PCI_MSI is not enabled\n",
			ent->device);
		dd = ERR_PTR(-ENODEV);
#endif
		break;

	case PCI_DEVICE_ID_QLOGIC_IB_7220:
		dd = qib_init_iba7220_funcs(pdev, ent);
		break;

	case PCI_DEVICE_ID_QLOGIC_IB_7322:
		dd = qib_init_iba7322_funcs(pdev, ent);
		break;

	default:
		qib_early_err(&pdev->dev,
			"Failing on unknown Intel deviceid 0x%x\n",
			ent->device);
		ret = -ENODEV;
	}

	if (IS_ERR(dd))
		ret = PTR_ERR(dd);
	if (ret)
		goto bail; /* error already printed */

	ret = qib_create_workqueues(dd);
	if (ret)
		goto bail;

	/* do the generic initialization */
	initfail = qib_init(dd, 0);

	ret = qib_register_ib_device(dd);

	/*
	 * Now ready for use.  this should be cleared whenever we
	 * detect a reset, or initiate one.  If earlier failure,
	 * we still create devices, so diags, etc. can be used
	 * to determine cause of problem.
	 */
	if (!qib_mini_init && !initfail && !ret)
		dd->flags |= QIB_INITTED;

	j = qib_device_create(dd);
	if (j)
		qib_dev_err(dd, "Failed to create /dev devices: %d\n", -j);
	j = qibfs_add(dd);
	if (j)
		qib_dev_err(dd, "Failed filesystem setup for counters: %d\n",
			    -j);

	if (qib_mini_init || initfail || ret) {
		qib_stop_timers(dd);
		flush_workqueue(ib_wq);
		for (pidx = 0; pidx < dd->num_pports; ++pidx)
			dd->f_quiet_serdes(dd->pport + pidx);
		if (qib_mini_init)
			goto bail;
		if (!j) {
			(void) qibfs_remove(dd);
			qib_device_remove(dd);
		}
		if (!ret)
			qib_unregister_ib_device(dd);
		qib_postinit_cleanup(dd);
		if (initfail)
			ret = initfail;
		goto bail;
	}

	ret = qib_enable_wc(dd);
	if (ret) {
		qib_dev_err(dd,
			"Write combining not enabled (err %d): performance may be poor\n",
			-ret);
		ret = 0;
	}

	qib_verify_pioperf(dd);
bail:
	return ret;
}