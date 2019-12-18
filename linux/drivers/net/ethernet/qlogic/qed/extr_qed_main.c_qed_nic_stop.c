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
struct qed_hwfn {int b_sp_dpc_enabled; int /*<<< orphan*/  sp_dpc; } ;
struct qed_dev {int num_hwfns; struct qed_hwfn* hwfns; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 int /*<<< orphan*/  qed_dbg_pf_exit (struct qed_dev*) ; 
 int qed_hw_stop (struct qed_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_nic_stop(struct qed_dev *cdev)
{
	int i, rc;

	rc = qed_hw_stop(cdev);

	for (i = 0; i < cdev->num_hwfns; i++) {
		struct qed_hwfn *p_hwfn = &cdev->hwfns[i];

		if (p_hwfn->b_sp_dpc_enabled) {
			tasklet_disable(p_hwfn->sp_dpc);
			p_hwfn->b_sp_dpc_enabled = false;
			DP_VERBOSE(cdev, NETIF_MSG_IFDOWN,
				   "Disabled sp tasklet [hwfn %d] at %p\n",
				   i, p_hwfn->sp_dpc);
		}
	}

	qed_dbg_pf_exit(cdev);

	return rc;
}