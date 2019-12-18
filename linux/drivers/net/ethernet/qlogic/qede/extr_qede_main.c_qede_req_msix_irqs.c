#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qede_fastpath {int type; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int msix_cnt; int /*<<< orphan*/  used_cnt; TYPE_2__* msix; } ;
struct qede_dev {TYPE_3__ int_info; struct qede_fastpath* fp_array; TYPE_1__* ndev; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {scalar_t__ rx_cpu_rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,struct qede_fastpath*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int QEDE_FASTPATH_RX ; 
 int QEDE_QUEUE_CNT (struct qede_dev*) ; 
 int irq_cpu_rmap_add (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_free_arfs (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_msix_fp_int ; 
 int /*<<< orphan*/  qede_sync_free_irqs (struct qede_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qede_fastpath*) ; 

__attribute__((used)) static int qede_req_msix_irqs(struct qede_dev *edev)
{
	int i, rc;

	/* Sanitize number of interrupts == number of prepared RSS queues */
	if (QEDE_QUEUE_CNT(edev) > edev->int_info.msix_cnt) {
		DP_ERR(edev,
		       "Interrupt mismatch: %d RSS queues > %d MSI-x vectors\n",
		       QEDE_QUEUE_CNT(edev), edev->int_info.msix_cnt);
		return -EINVAL;
	}

	for (i = 0; i < QEDE_QUEUE_CNT(edev); i++) {
#ifdef CONFIG_RFS_ACCEL
		struct qede_fastpath *fp = &edev->fp_array[i];

		if (edev->ndev->rx_cpu_rmap && (fp->type & QEDE_FASTPATH_RX)) {
			rc = irq_cpu_rmap_add(edev->ndev->rx_cpu_rmap,
					      edev->int_info.msix[i].vector);
			if (rc) {
				DP_ERR(edev, "Failed to add CPU rmap\n");
				qede_free_arfs(edev);
			}
		}
#endif
		rc = request_irq(edev->int_info.msix[i].vector,
				 qede_msix_fp_int, 0, edev->fp_array[i].name,
				 &edev->fp_array[i]);
		if (rc) {
			DP_ERR(edev, "Request fp %d irq failed\n", i);
			qede_sync_free_irqs(edev);
			return rc;
		}
		DP_VERBOSE(edev, NETIF_MSG_INTR,
			   "Requested fp irq for %s [entry %d]. Cookie is at %p\n",
			   edev->fp_array[i].name, i,
			   &edev->fp_array[i]);
		edev->int_info.used_cnt++;
	}

	return 0;
}