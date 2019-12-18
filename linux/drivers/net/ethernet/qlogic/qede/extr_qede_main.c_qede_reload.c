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
struct qede_reload_args {int /*<<< orphan*/  (* func ) (struct qede_dev*,struct qede_reload_args*) ;} ;
struct qede_dev {scalar_t__ state; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDE_LOAD_RELOAD ; 
 scalar_t__ QEDE_STATE_OPEN ; 
 int /*<<< orphan*/  QEDE_UNLOAD_NORMAL ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_config_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_load (struct qede_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qede_unload (struct qede_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct qede_dev*,struct qede_reload_args*) ; 
 int /*<<< orphan*/  stub2 (struct qede_dev*,struct qede_reload_args*) ; 

void qede_reload(struct qede_dev *edev,
		 struct qede_reload_args *args, bool is_locked)
{
	if (!is_locked)
		__qede_lock(edev);

	/* Since qede_lock is held, internal state wouldn't change even
	 * if netdev state would start transitioning. Check whether current
	 * internal configuration indicates device is up, then reload.
	 */
	if (edev->state == QEDE_STATE_OPEN) {
		qede_unload(edev, QEDE_UNLOAD_NORMAL, true);
		if (args)
			args->func(edev, args);
		qede_load(edev, QEDE_LOAD_RELOAD, true);

		/* Since no one is going to do it for us, re-configure */
		qede_config_rx_mode(edev->ndev);
	} else if (args) {
		args->func(edev, args);
	}

	if (!is_locked)
		__qede_unlock(edev);
}