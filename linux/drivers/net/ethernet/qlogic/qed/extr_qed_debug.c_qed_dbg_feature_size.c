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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct TYPE_3__ {size_t engine_for_debug; struct qed_dbg_feature* features; } ;
struct qed_dev {TYPE_1__ dbg_params; struct qed_hwfn* hwfns; } ;
struct qed_dbg_feature {int buf_size; } ;
typedef  enum qed_dbg_features { ____Placeholder_qed_dbg_features } qed_dbg_features ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_4__ {int (* get_size ) (struct qed_hwfn*,struct qed_ptt*,int*) ;} ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int EINVAL ; 
 TYPE_2__* qed_features_lookup ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int stub1 (struct qed_hwfn*,struct qed_ptt*,int*) ; 

int qed_dbg_feature_size(struct qed_dev *cdev, enum qed_dbg_features feature)
{
	struct qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->dbg_params.engine_for_debug];
	struct qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	struct qed_dbg_feature *qed_feature =
		&cdev->dbg_params.features[feature];
	u32 buf_size_dwords;
	enum dbg_status rc;

	if (!p_ptt)
		return -EINVAL;

	rc = qed_features_lookup[feature].get_size(p_hwfn, p_ptt,
						   &buf_size_dwords);
	if (rc != DBG_STATUS_OK)
		buf_size_dwords = 0;

	qed_ptt_release(p_hwfn, p_ptt);
	qed_feature->buf_size = buf_size_dwords * sizeof(u32);
	return qed_feature->buf_size;
}