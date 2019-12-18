#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qede_tx_queue {scalar_t__ sw_tx_cons; scalar_t__ sw_tx_prod; int /*<<< orphan*/  index; } ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int (* drain ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int ENODEV ; 
 int /*<<< orphan*/  barrier () ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qede_drain_txq(struct qede_dev *edev,
			  struct qede_tx_queue *txq, bool allow_drain)
{
	int rc, cnt = 1000;

	while (txq->sw_tx_cons != txq->sw_tx_prod) {
		if (!cnt) {
			if (allow_drain) {
				DP_NOTICE(edev,
					  "Tx queue[%d] is stuck, requesting MCP to drain\n",
					  txq->index);
				rc = edev->ops->common->drain(edev->cdev);
				if (rc)
					return rc;
				return qede_drain_txq(edev, txq, false);
			}
			DP_NOTICE(edev,
				  "Timeout waiting for tx queue[%d]: PROD=%d, CONS=%d\n",
				  txq->index, txq->sw_tx_prod,
				  txq->sw_tx_cons);
			return -ENODEV;
		}
		cnt--;
		usleep_range(1000, 2000);
		barrier();
	}

	/* FW finished processing, wait for HW to transmit all tx packets */
	usleep_range(1000, 2000);

	return 0;
}