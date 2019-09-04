#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct qed_hwfn {int my_id; int abs_pf_id; struct qed_dev* sp_dpc; int /*<<< orphan*/  name; struct qed_dev* cdev; } ;
struct TYPE_8__ {scalar_t__ int_mode; } ;
struct TYPE_9__ {TYPE_3__ out; TYPE_1__* msix_table; } ;
struct qed_dev {int /*<<< orphan*/  name; TYPE_5__* pdev; TYPE_4__ int_params; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_7__ {int number; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,char*) ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  NAME_SIZE ; 
 int NETIF_MSG_INTR ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ QED_INT_MODE_INTA ; 
 scalar_t__ QED_INT_MODE_MSIX ; 
 int QED_MSG_SP ; 
 int /*<<< orphan*/  qed_msix_sp_int ; 
 int /*<<< orphan*/  qed_single_int ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct qed_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,...) ; 

int qed_slowpath_irq_req(struct qed_hwfn *hwfn)
{
	struct qed_dev *cdev = hwfn->cdev;
	u32 int_mode;
	int rc = 0;
	u8 id;

	int_mode = cdev->int_params.out.int_mode;
	if (int_mode == QED_INT_MODE_MSIX) {
		id = hwfn->my_id;
		snprintf(hwfn->name, NAME_SIZE, "sp-%d-%02x:%02x.%02x",
			 id, cdev->pdev->bus->number,
			 PCI_SLOT(cdev->pdev->devfn), hwfn->abs_pf_id);
		rc = request_irq(cdev->int_params.msix_table[id].vector,
				 qed_msix_sp_int, 0, hwfn->name, hwfn->sp_dpc);
	} else {
		unsigned long flags = 0;

		snprintf(cdev->name, NAME_SIZE, "%02x:%02x.%02x",
			 cdev->pdev->bus->number, PCI_SLOT(cdev->pdev->devfn),
			 PCI_FUNC(cdev->pdev->devfn));

		if (cdev->int_params.out.int_mode == QED_INT_MODE_INTA)
			flags |= IRQF_SHARED;

		rc = request_irq(cdev->pdev->irq, qed_single_int,
				 flags, cdev->name, cdev);
	}

	if (rc)
		DP_NOTICE(cdev, "request_irq failed, rc = %d\n", rc);
	else
		DP_VERBOSE(hwfn, (NETIF_MSG_INTR | QED_MSG_SP),
			   "Requested slowpath %s\n",
			   (int_mode == QED_INT_MODE_MSIX) ? "MSI-X" : "IRQ");

	return rc;
}