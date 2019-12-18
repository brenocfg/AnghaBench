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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct qed_llh_info {struct qed_llh_filter_info** pp_filters; } ;
struct qed_llh_filter_info {int b_enabled; int type; scalar_t__ ref_cnt; int /*<<< orphan*/  filter; } ;
struct qed_dev {struct qed_llh_info* p_llh_info; } ;
typedef  enum qed_llh_filter_type { ____Placeholder_qed_llh_filter_type } qed_llh_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union qed_llh_filter*,int) ; 
 int qed_llh_shadow_sanity (struct qed_dev*,size_t,size_t,char*) ; 

__attribute__((used)) static int
__qed_llh_shadow_add_filter(struct qed_dev *cdev,
			    u8 ppfid,
			    u8 filter_idx,
			    enum qed_llh_filter_type type,
			    union qed_llh_filter *p_filter, u32 *p_ref_cnt)
{
	struct qed_llh_info *p_llh_info = cdev->p_llh_info;
	struct qed_llh_filter_info *p_filters;
	int rc;

	rc = qed_llh_shadow_sanity(cdev, ppfid, filter_idx, "add");
	if (rc)
		return rc;

	p_filters = p_llh_info->pp_filters[ppfid];
	if (!p_filters[filter_idx].ref_cnt) {
		p_filters[filter_idx].b_enabled = true;
		p_filters[filter_idx].type = type;
		memcpy(&p_filters[filter_idx].filter, p_filter,
		       sizeof(p_filters[filter_idx].filter));
	}

	*p_ref_cnt = ++p_filters[filter_idx].ref_cnt;

	return 0;
}