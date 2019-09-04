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
typedef  int /*<<< orphan*/  u8 ;
struct qed_ll2_params {int dummy; } ;
struct qed_ll2_acquire_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_ooo_queue_id; } ;
struct TYPE_4__ {TYPE_1__ iscsi_pf_params; } ;
struct qed_hwfn {TYPE_2__ pf_params; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  QED_LL2_UNUSED_HANDLE ; 
 int qed_ll2_acquire_connection (struct qed_hwfn*,struct qed_ll2_acquire_data*) ; 
 int qed_ll2_establish_connection (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_release_connection (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_set_conn_data (struct qed_dev*,struct qed_ll2_acquire_data*,struct qed_ll2_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qed_ll2_start_ooo(struct qed_dev *cdev,
			     struct qed_ll2_params *params)
{
	struct qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	u8 *handle = &hwfn->pf_params.iscsi_pf_params.ll2_ooo_queue_id;
	struct qed_ll2_acquire_data data;
	int rc;

	qed_ll2_set_conn_data(cdev, &data, params,
			      QED_LL2_TYPE_OOO, handle, true);

	rc = qed_ll2_acquire_connection(hwfn, &data);
	if (rc) {
		DP_INFO(cdev, "Failed to acquire LL2 OOO connection\n");
		goto out;
	}

	rc = qed_ll2_establish_connection(hwfn, *handle);
	if (rc) {
		DP_INFO(cdev, "Failed to establist LL2 OOO connection\n");
		goto fail;
	}

	return 0;

fail:
	qed_ll2_release_connection(hwfn, *handle);
out:
	*handle = QED_LL2_UNUSED_HANDLE;
	return rc;
}