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
typedef  int /*<<< orphan*/  u8 ;
struct qed_dev {scalar_t__ l2_affin_hint; int /*<<< orphan*/  iwarp_cmt; } ;
typedef  enum qed_eng { ____Placeholder_qed_eng } qed_eng ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int,char*,int) ; 
 int EINVAL ; 
 int QED_BOTH_ENG ; 
 int QED_ENG0 ; 
 int QED_ENG1 ; 
 int QED_MSG_RDMA ; 
 int QED_MSG_SP ; 
 int qed_llh_set_ppfid_affinity (struct qed_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_iwarp_set_engine_affin(struct qed_dev *cdev, bool b_reset)
{
	enum qed_eng eng;
	u8 ppfid = 0;
	int rc;

	/* Make sure iwarp cmt mode is enabled before setting affinity */
	if (!cdev->iwarp_cmt)
		return -EINVAL;

	if (b_reset)
		eng = QED_BOTH_ENG;
	else
		eng = cdev->l2_affin_hint ? QED_ENG1 : QED_ENG0;

	rc = qed_llh_set_ppfid_affinity(cdev, ppfid, eng);
	if (rc) {
		DP_NOTICE(cdev,
			  "Failed to set the engine affinity of ppfid %d\n",
			  ppfid);
		return rc;
	}

	DP_VERBOSE(cdev, (QED_MSG_RDMA | QED_MSG_SP),
		   "LLH: Set the engine affinity of non-RoCE packets as %d\n",
		   eng);

	return 0;
}