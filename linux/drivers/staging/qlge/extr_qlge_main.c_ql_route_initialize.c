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
struct ql_adapter {int rss_ring_count; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_IDX_BCAST ; 
 int /*<<< orphan*/  RT_IDX_BCAST_SLOT ; 
 int /*<<< orphan*/  RT_IDX_CAM_HIT ; 
 int /*<<< orphan*/  RT_IDX_CAM_HIT_SLOT ; 
 int /*<<< orphan*/  RT_IDX_IP_CSUM_ERR ; 
 int /*<<< orphan*/  RT_IDX_IP_CSUM_ERR_SLOT ; 
 int /*<<< orphan*/  RT_IDX_RSS_MATCH ; 
 int /*<<< orphan*/  RT_IDX_RSS_MATCH_SLOT ; 
 int /*<<< orphan*/  RT_IDX_TCP_UDP_CSUM_ERR_SLOT ; 
 int /*<<< orphan*/  RT_IDX_TU_CSUM_ERR ; 
 int /*<<< orphan*/  SEM_RT_IDX_MASK ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_clear_routing_entries (struct ql_adapter*) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_set_routing_reg (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_route_initialize(struct ql_adapter *qdev)
{
	int status = 0;

	/* Clear all the entries in the routing table. */
	status = ql_clear_routing_entries(qdev);
	if (status)
		return status;

	status = ql_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	if (status)
		return status;

	status = ql_set_routing_reg(qdev, RT_IDX_IP_CSUM_ERR_SLOT,
						RT_IDX_IP_CSUM_ERR, 1);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev,
			"Failed to init routing register "
			"for IP CSUM error packets.\n");
		goto exit;
	}
	status = ql_set_routing_reg(qdev, RT_IDX_TCP_UDP_CSUM_ERR_SLOT,
						RT_IDX_TU_CSUM_ERR, 1);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev,
			"Failed to init routing register "
			"for TCP/UDP CSUM error packets.\n");
		goto exit;
	}
	status = ql_set_routing_reg(qdev, RT_IDX_BCAST_SLOT, RT_IDX_BCAST, 1);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Failed to init routing register for broadcast packets.\n");
		goto exit;
	}
	/* If we have more than one inbound queue, then turn on RSS in the
	 * routing block.
	 */
	if (qdev->rss_ring_count > 1) {
		status = ql_set_routing_reg(qdev, RT_IDX_RSS_MATCH_SLOT,
					RT_IDX_RSS_MATCH, 1);
		if (status) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Failed to init routing register for MATCH RSS packets.\n");
			goto exit;
		}
	}

	status = ql_set_routing_reg(qdev, RT_IDX_CAM_HIT_SLOT,
				    RT_IDX_CAM_HIT, 1);
	if (status)
		netif_err(qdev, ifup, qdev->ndev,
			  "Failed to init routing register for CAM packets.\n");
exit:
	ql_sem_unlock(qdev, SEM_RT_IDX_MASK);
	return status;
}