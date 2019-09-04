#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct qed_dbg_feature* features; } ;
struct qed_dev {TYPE_1__ dbg_params; } ;
struct qed_dbg_feature {int /*<<< orphan*/ * dump_buf; } ;
typedef  enum qed_dbg_features { ____Placeholder_qed_dbg_features } qed_dbg_features ;

/* Variables and functions */
 int DBG_FEATURE_NUM ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void qed_dbg_pf_exit(struct qed_dev *cdev)
{
	struct qed_dbg_feature *feature = NULL;
	enum qed_dbg_features feature_idx;

	/* Debug features' buffers may be allocated if debug feature was used
	 * but dump wasn't called.
	 */
	for (feature_idx = 0; feature_idx < DBG_FEATURE_NUM; feature_idx++) {
		feature = &cdev->dbg_params.features[feature_idx];
		if (feature->dump_buf) {
			vfree(feature->dump_buf);
			feature->dump_buf = NULL;
		}
	}
}