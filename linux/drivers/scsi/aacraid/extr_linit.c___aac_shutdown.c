#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fib {int /*<<< orphan*/  event_wait; TYPE_3__* hw_fib_va; } ;
struct aac_dev {int adapter_shutdown; int max_msix; TYPE_4__* pdev; scalar_t__ msi; struct aac_dev* aac_msix; int /*<<< orphan*/ * thread; struct fib* fibs; TYPE_1__* scsi_host_ptr; scalar_t__ aif_thread; int /*<<< orphan*/  ioctl_mutex; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int XferState; } ;
struct TYPE_9__ {TYPE_2__ header; } ;
struct TYPE_7__ {int can_queue; } ;

/* Variables and functions */
 int AAC_NUM_MGT_FIB ; 
 int Async ; 
 int NoResponseExpected ; 
 int ResponseExpected ; 
 int /*<<< orphan*/  aac_adapter_disable_int (struct aac_dev*) ; 
 scalar_t__ aac_is_src (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_send_shutdown (struct aac_dev*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct aac_dev*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_4__*,int) ; 

__attribute__((used)) static void __aac_shutdown(struct aac_dev * aac)
{
	int i;

	mutex_lock(&aac->ioctl_mutex);
	aac->adapter_shutdown = 1;
	mutex_unlock(&aac->ioctl_mutex);

	if (aac->aif_thread) {
		int i;
		/* Clear out events first */
		for (i = 0; i < (aac->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB); i++) {
			struct fib *fib = &aac->fibs[i];
			if (!(fib->hw_fib_va->header.XferState & cpu_to_le32(NoResponseExpected | Async)) &&
			    (fib->hw_fib_va->header.XferState & cpu_to_le32(ResponseExpected)))
				complete(&fib->event_wait);
		}
		kthread_stop(aac->thread);
		aac->thread = NULL;
	}

	aac_send_shutdown(aac);

	aac_adapter_disable_int(aac);

	if (aac_is_src(aac)) {
		if (aac->max_msix > 1) {
			for (i = 0; i < aac->max_msix; i++) {
				free_irq(pci_irq_vector(aac->pdev, i),
					 &(aac->aac_msix[i]));
			}
		} else {
			free_irq(aac->pdev->irq,
				 &(aac->aac_msix[0]));
		}
	} else {
		free_irq(aac->pdev->irq, aac);
	}
	if (aac->msi)
		pci_disable_msi(aac->pdev);
	else if (aac->max_msix > 1)
		pci_disable_msix(aac->pdev);
}