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
struct qede_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; } ;
struct qed_link_output {scalar_t__ link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  QEDE_FLAGS_LINK_REQUESTED ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_rdma_dev_event_close (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_dev_event_open (struct qede_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_link_update(void *dev, struct qed_link_output *link)
{
	struct qede_dev *edev = dev;

	if (!test_bit(QEDE_FLAGS_LINK_REQUESTED, &edev->flags)) {
		DP_VERBOSE(edev, NETIF_MSG_LINK, "Interface is not ready\n");
		return;
	}

	if (link->link_up) {
		if (!netif_carrier_ok(edev->ndev)) {
			DP_NOTICE(edev, "Link is up\n");
			netif_tx_start_all_queues(edev->ndev);
			netif_carrier_on(edev->ndev);
			qede_rdma_dev_event_open(edev);
		}
	} else {
		if (netif_carrier_ok(edev->ndev)) {
			DP_NOTICE(edev, "Link is down\n");
			netif_tx_disable(edev->ndev);
			netif_carrier_off(edev->ndev);
			qede_rdma_dev_event_close(edev);
		}
	}
}