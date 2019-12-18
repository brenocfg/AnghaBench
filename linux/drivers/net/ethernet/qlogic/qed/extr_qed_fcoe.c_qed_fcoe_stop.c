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
struct qed_ptt {int dummy; } ;
struct qed_dev {int flags; int /*<<< orphan*/  connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int QED_FLAG_STORAGE_STARTED ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  hash_empty (int /*<<< orphan*/ ) ; 
 struct qed_ptt* qed_ptt_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ptt_release (int /*<<< orphan*/ ,struct qed_ptt*) ; 
 int qed_sp_fcoe_func_stop (int /*<<< orphan*/ ,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_fcoe_stop(struct qed_dev *cdev)
{
	struct qed_ptt *p_ptt;
	int rc;

	if (!(cdev->flags & QED_FLAG_STORAGE_STARTED)) {
		DP_NOTICE(cdev, "fcoe already stopped\n");
		return 0;
	}

	if (!hash_empty(cdev->connections)) {
		DP_NOTICE(cdev,
			  "Can't stop fcoe - not all connections were returned\n");
		return -EINVAL;
	}

	p_ptt = qed_ptt_acquire(QED_AFFIN_HWFN(cdev));
	if (!p_ptt)
		return -EAGAIN;

	/* Stop the fcoe */
	rc = qed_sp_fcoe_func_stop(QED_AFFIN_HWFN(cdev), p_ptt,
				   QED_SPQ_MODE_EBLOCK, NULL);
	cdev->flags &= ~QED_FLAG_STORAGE_STARTED;
	qed_ptt_release(QED_AFFIN_HWFN(cdev), p_ptt);

	return rc;
}