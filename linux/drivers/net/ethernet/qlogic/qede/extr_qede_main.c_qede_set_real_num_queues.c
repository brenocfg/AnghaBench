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
struct TYPE_2__ {int num_tc; } ;
struct qede_dev {int /*<<< orphan*/  ndev; TYPE_1__ dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  QEDE_RSS_COUNT (struct qede_dev*) ; 
 int QEDE_TSS_COUNT (struct qede_dev*) ; 
 int netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qede_set_real_num_queues(struct qede_dev *edev)
{
	int rc = 0;

	rc = netif_set_real_num_tx_queues(edev->ndev,
					  QEDE_TSS_COUNT(edev) *
					  edev->dev_info.num_tc);
	if (rc) {
		DP_NOTICE(edev, "Failed to set real number of Tx queues\n");
		return rc;
	}

	rc = netif_set_real_num_rx_queues(edev->ndev, QEDE_RSS_COUNT(edev));
	if (rc) {
		DP_NOTICE(edev, "Failed to set real number of Rx queues\n");
		return rc;
	}

	return 0;
}