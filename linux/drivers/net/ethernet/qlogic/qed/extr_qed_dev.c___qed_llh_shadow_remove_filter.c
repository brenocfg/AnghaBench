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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct qed_llh_info {struct qed_llh_filter_info** pp_filters; } ;
struct qed_llh_filter_info {scalar_t__ ref_cnt; } ;
struct qed_dev {struct qed_llh_info* p_llh_info; } ;
typedef  int /*<<< orphan*/  p_filters ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct qed_llh_filter_info*,int /*<<< orphan*/ ,int) ; 
 int qed_llh_shadow_sanity (struct qed_dev*,size_t,size_t,char*) ; 

__attribute__((used)) static int
__qed_llh_shadow_remove_filter(struct qed_dev *cdev,
			       u8 ppfid, u8 filter_idx, u32 *p_ref_cnt)
{
	struct qed_llh_info *p_llh_info = cdev->p_llh_info;
	struct qed_llh_filter_info *p_filters;
	int rc;

	rc = qed_llh_shadow_sanity(cdev, ppfid, filter_idx, "remove");
	if (rc)
		return rc;

	p_filters = p_llh_info->pp_filters[ppfid];
	if (!p_filters[filter_idx].ref_cnt) {
		DP_NOTICE(cdev,
			  "LLH shadow: trying to remove a filter with ref_cnt=0\n");
		return -EINVAL;
	}

	*p_ref_cnt = --p_filters[filter_idx].ref_cnt;
	if (!p_filters[filter_idx].ref_cnt)
		memset(&p_filters[filter_idx],
		       0, sizeof(p_filters[filter_idx]));

	return 0;
}