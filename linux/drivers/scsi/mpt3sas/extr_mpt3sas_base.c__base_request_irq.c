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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct adapter_reply_queue {int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/  busy; int /*<<< orphan*/  msix_index; struct MPT3SAS_ADAPTER* ioc; } ;
struct MPT3SAS_ADAPTER {char* driver_name; int id; int /*<<< orphan*/  reply_queue_list; scalar_t__ msix_enable; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MPT_NAME_LENGTH ; 
 int /*<<< orphan*/  _base_interrupt ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_err (struct MPT3SAS_ADAPTER*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct adapter_reply_queue*) ; 
 struct adapter_reply_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adapter_reply_queue*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int,...) ; 

__attribute__((used)) static int
_base_request_irq(struct MPT3SAS_ADAPTER *ioc, u8 index)
{
	struct pci_dev *pdev = ioc->pdev;
	struct adapter_reply_queue *reply_q;
	int r;

	reply_q =  kzalloc(sizeof(struct adapter_reply_queue), GFP_KERNEL);
	if (!reply_q) {
		ioc_err(ioc, "unable to allocate memory %zu!\n",
			sizeof(struct adapter_reply_queue));
		return -ENOMEM;
	}
	reply_q->ioc = ioc;
	reply_q->msix_index = index;

	atomic_set(&reply_q->busy, 0);
	if (ioc->msix_enable)
		snprintf(reply_q->name, MPT_NAME_LENGTH, "%s%d-msix%d",
		    ioc->driver_name, ioc->id, index);
	else
		snprintf(reply_q->name, MPT_NAME_LENGTH, "%s%d",
		    ioc->driver_name, ioc->id);
	r = request_irq(pci_irq_vector(pdev, index), _base_interrupt,
			IRQF_SHARED, reply_q->name, reply_q);
	if (r) {
		pr_err("%s: unable to allocate interrupt %d!\n",
		       reply_q->name, pci_irq_vector(pdev, index));
		kfree(reply_q);
		return -EBUSY;
	}

	INIT_LIST_HEAD(&reply_q->list);
	list_add_tail(&reply_q->list, &ioc->reply_queue_list);
	return 0;
}