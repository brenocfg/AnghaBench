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
typedef  int /*<<< orphan*/  u64 ;
struct qede_dev {int /*<<< orphan*/  arfs; } ;
struct qede_arfs_fltr_node {int /*<<< orphan*/  rxq_id; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  QEDE_ARFS_BUCKET_HEAD (struct qede_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_configure_arfs_fltr (struct qede_dev*,struct qede_arfs_fltr_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qede_dequeue_fltr_and_config_searcher (struct qede_dev*,struct qede_arfs_fltr_node*) ; 
 struct qede_arfs_fltr_node* qede_get_arfs_fltr_by_loc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qede_poll_arfs_filter_config (struct qede_dev*,struct qede_arfs_fltr_node*) ; 

int qede_delete_flow_filter(struct qede_dev *edev, u64 cookie)
{
	struct qede_arfs_fltr_node *fltr = NULL;
	int rc = -EPERM;

	__qede_lock(edev);
	if (!edev->arfs)
		goto unlock;

	fltr = qede_get_arfs_fltr_by_loc(QEDE_ARFS_BUCKET_HEAD(edev, 0),
					 cookie);
	if (!fltr)
		goto unlock;

	qede_configure_arfs_fltr(edev, fltr, fltr->rxq_id, false);

	rc = qede_poll_arfs_filter_config(edev, fltr);
	if (rc == 0)
		qede_dequeue_fltr_and_config_searcher(edev, fltr);

unlock:
	__qede_unlock(edev);
	return rc;
}