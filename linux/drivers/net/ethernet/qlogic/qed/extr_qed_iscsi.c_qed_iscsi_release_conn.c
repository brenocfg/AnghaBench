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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hash_iscsi_con {int /*<<< orphan*/  con; int /*<<< orphan*/  node; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qed_hash_iscsi_con*) ; 
 struct qed_hash_iscsi_con* qed_iscsi_get_hash (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iscsi_release_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_iscsi_release_conn(struct qed_dev *cdev, u32 handle)
{
	struct qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	if (!hash_con) {
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		return -EINVAL;
	}

	hlist_del(&hash_con->node);
	qed_iscsi_release_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kfree(hash_con);

	return 0;
}