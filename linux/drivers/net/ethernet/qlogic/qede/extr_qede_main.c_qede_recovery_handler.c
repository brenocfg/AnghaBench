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
typedef  scalar_t__ u32 ;
struct qede_dev {scalar_t__ state; int /*<<< orphan*/  ndev; int /*<<< orphan*/ * cdev; int /*<<< orphan*/  dp_level; int /*<<< orphan*/  dp_module; int /*<<< orphan*/  pdev; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* recovery_prolog ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  IS_VF (struct qede_dev*) ; 
 int /*<<< orphan*/  QEDE_LOAD_RECOVERY ; 
 int /*<<< orphan*/  QEDE_PROBE_RECOVERY ; 
 int /*<<< orphan*/  QEDE_REMOVE_RECOVERY ; 
 scalar_t__ QEDE_STATE_OPEN ; 
 scalar_t__ QEDE_STATE_RECOVERY ; 
 int /*<<< orphan*/  QEDE_UNLOAD_RECOVERY ; 
 int __qede_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qede_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_config_rx_mode (int /*<<< orphan*/ ) ; 
 int qede_load (struct qede_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qede_recovery_failed (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_unload (struct qede_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_recovery_handler(struct qede_dev *edev)
{
	u32 curr_state = edev->state;
	int rc;

	DP_NOTICE(edev, "Starting a recovery process\n");

	/* No need to acquire first the qede_lock since is done by qede_sp_task
	 * before calling this function.
	 */
	edev->state = QEDE_STATE_RECOVERY;

	edev->ops->common->recovery_prolog(edev->cdev);

	if (curr_state == QEDE_STATE_OPEN)
		qede_unload(edev, QEDE_UNLOAD_RECOVERY, true);

	__qede_remove(edev->pdev, QEDE_REMOVE_RECOVERY);

	rc = __qede_probe(edev->pdev, edev->dp_module, edev->dp_level,
			  IS_VF(edev), QEDE_PROBE_RECOVERY);
	if (rc) {
		edev->cdev = NULL;
		goto err;
	}

	if (curr_state == QEDE_STATE_OPEN) {
		rc = qede_load(edev, QEDE_LOAD_RECOVERY, true);
		if (rc)
			goto err;

		qede_config_rx_mode(edev->ndev);
		udp_tunnel_get_rx_info(edev->ndev);
	}

	edev->state = curr_state;

	DP_NOTICE(edev, "Recovery handling is done\n");

	return;

err:
	qede_recovery_failed(edev);
}