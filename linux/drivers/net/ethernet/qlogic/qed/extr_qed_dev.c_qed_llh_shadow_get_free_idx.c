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
struct qed_llh_info {struct qed_llh_filter_info** pp_filters; } ;
struct qed_llh_filter_info {int /*<<< orphan*/  b_enabled; } ;
struct qed_dev {struct qed_llh_info* p_llh_info; } ;

/* Variables and functions */
 size_t NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 size_t QED_LLH_INVALID_FILTER_IDX ; 
 int qed_llh_shadow_sanity (struct qed_dev*,size_t,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
qed_llh_shadow_get_free_idx(struct qed_dev *cdev, u8 ppfid, u8 *p_filter_idx)
{
	struct qed_llh_info *p_llh_info = cdev->p_llh_info;
	struct qed_llh_filter_info *p_filters;
	int rc;
	u8 i;

	rc = qed_llh_shadow_sanity(cdev, ppfid, 0, "get_free_idx");
	if (rc)
		return rc;

	*p_filter_idx = QED_LLH_INVALID_FILTER_IDX;

	p_filters = p_llh_info->pp_filters[ppfid];
	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		if (!p_filters[i].b_enabled) {
			*p_filter_idx = i;
			break;
		}
	}

	return 0;
}