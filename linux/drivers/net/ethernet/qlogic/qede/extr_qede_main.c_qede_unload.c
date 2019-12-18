#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_hwfns; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
struct qede_dev {scalar_t__ ptp_skip_txts; int /*<<< orphan*/  cdev; TYPE_4__* ops; TYPE_2__ dev_info; int /*<<< orphan*/  ndev; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;
struct qed_link_params {int link_up; } ;
typedef  int /*<<< orphan*/  link_params ;
typedef  enum qede_unload_mode { ____Placeholder_qede_unload_mode } qede_unload_mode ;
struct TYPE_8__ {TYPE_3__* common; int /*<<< orphan*/  (* fastpath_stop ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_fp_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  IS_VF (struct qede_dev*) ; 
 int /*<<< orphan*/  QEDE_FLAGS_LINK_REQUESTED ; 
 int /*<<< orphan*/  QEDE_STATE_CLOSED ; 
 int QEDE_UNLOAD_RECOVERY ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct qed_link_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_empty_tx_queues (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_free_arfs (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_free_fp_array (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_free_mem_load (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_napi_disable_remove (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_poll_for_freeing_arfs_filters (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_dev_event_close (struct qede_dev*) ; 
 int qede_stop_queues (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_sync_free_irqs (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_vlan_mark_nonconfigured (struct qede_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_link_params*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_unload(struct qede_dev *edev, enum qede_unload_mode mode,
			bool is_locked)
{
	struct qed_link_params link_params;
	int rc;

	DP_INFO(edev, "Starting qede unload\n");

	if (!is_locked)
		__qede_lock(edev);

	clear_bit(QEDE_FLAGS_LINK_REQUESTED, &edev->flags);

	if (mode != QEDE_UNLOAD_RECOVERY)
		edev->state = QEDE_STATE_CLOSED;

	qede_rdma_dev_event_close(edev);

	/* Close OS Tx */
	netif_tx_disable(edev->ndev);
	netif_carrier_off(edev->ndev);

	if (mode != QEDE_UNLOAD_RECOVERY) {
		/* Reset the link */
		memset(&link_params, 0, sizeof(link_params));
		link_params.link_up = false;
		edev->ops->common->set_link(edev->cdev, &link_params);

		rc = qede_stop_queues(edev);
		if (rc) {
			qede_sync_free_irqs(edev);
			goto out;
		}

		DP_INFO(edev, "Stopped Queues\n");
	}

	qede_vlan_mark_nonconfigured(edev);
	edev->ops->fastpath_stop(edev->cdev);

	if (!IS_VF(edev) && edev->dev_info.common.num_hwfns == 1) {
		qede_poll_for_freeing_arfs_filters(edev);
		qede_free_arfs(edev);
	}

	/* Release the interrupts */
	qede_sync_free_irqs(edev);
	edev->ops->common->set_fp_int(edev->cdev, 0);

	qede_napi_disable_remove(edev);

	if (mode == QEDE_UNLOAD_RECOVERY)
		qede_empty_tx_queues(edev);

	qede_free_mem_load(edev);
	qede_free_fp_array(edev);

out:
	if (!is_locked)
		__qede_unlock(edev);

	if (mode != QEDE_UNLOAD_RECOVERY)
		DP_NOTICE(edev, "Link is down\n");

	edev->ptp_skip_txts = 0;

	DP_INFO(edev, "Ending qede unload\n");
}