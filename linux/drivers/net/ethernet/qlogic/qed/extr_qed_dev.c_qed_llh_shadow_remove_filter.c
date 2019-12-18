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
typedef  union qed_llh_filter {int dummy; } qed_llh_filter ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*) ; 
 int EINVAL ; 
 scalar_t__ QED_LLH_INVALID_FILTER_IDX ; 
 int __qed_llh_shadow_remove_filter (struct qed_dev*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int qed_llh_shadow_search_filter (struct qed_dev*,scalar_t__,union qed_llh_filter*,scalar_t__*) ; 

__attribute__((used)) static int
qed_llh_shadow_remove_filter(struct qed_dev *cdev,
			     u8 ppfid,
			     union qed_llh_filter *p_filter,
			     u8 *p_filter_idx, u32 *p_ref_cnt)
{
	int rc;

	rc = qed_llh_shadow_search_filter(cdev, ppfid, p_filter, p_filter_idx);
	if (rc)
		return rc;

	/* No matching filter was found */
	if (*p_filter_idx == QED_LLH_INVALID_FILTER_IDX) {
		DP_NOTICE(cdev, "Failed to find a filter in the LLH shadow\n");
		return -EINVAL;
	}

	return __qed_llh_shadow_remove_filter(cdev, ppfid, *p_filter_idx,
					      p_ref_cnt);
}