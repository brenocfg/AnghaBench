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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {int /*<<< orphan*/  pqinfo; int /*<<< orphan*/  nr_queues; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_pending_queue (struct cpt_vf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void vq_post_process(struct cpt_vf *cptvf, u32 qno)
{
	struct pci_dev *pdev = cptvf->pdev;

	if (unlikely(qno > cptvf->nr_queues)) {
		dev_err(&pdev->dev, "Request for post processing on invalid pending queue: %u\n",
			qno);
		return;
	}

	process_pending_queue(cptvf, &cptvf->pqinfo, qno);
}