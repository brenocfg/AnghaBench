#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_6__ {int msix_cnt; int /*<<< orphan*/  used_cnt; TYPE_1__* msix; } ;
struct qedr_dev {int num_cnq; int num_hwfns; size_t affin_hwfn_idx; TYPE_2__ int_info; TYPE_3__* cnq_array; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int /*<<< orphan*/  qedr_irq_handler ; 
 int /*<<< orphan*/  qedr_sync_free_irqs (struct qedr_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int qedr_req_msix_irqs(struct qedr_dev *dev)
{
	int i, rc = 0;
	u16 idx;

	if (dev->num_cnq > dev->int_info.msix_cnt) {
		DP_ERR(dev,
		       "Interrupt mismatch: %d CNQ queues > %d MSI-x vectors\n",
		       dev->num_cnq, dev->int_info.msix_cnt);
		return -EINVAL;
	}

	for (i = 0; i < dev->num_cnq; i++) {
		idx = i * dev->num_hwfns + dev->affin_hwfn_idx;
		rc = request_irq(dev->int_info.msix[idx].vector,
				 qedr_irq_handler, 0, dev->cnq_array[i].name,
				 &dev->cnq_array[i]);
		if (rc) {
			DP_ERR(dev, "Request cnq %d irq failed\n", i);
			qedr_sync_free_irqs(dev);
		} else {
			DP_DEBUG(dev, QEDR_MSG_INIT,
				 "Requested cnq irq for %s [entry %d]. Cookie is at %p\n",
				 dev->cnq_array[i].name, i,
				 &dev->cnq_array[i]);
			dev->int_info.used_cnt++;
		}
	}

	return rc;
}