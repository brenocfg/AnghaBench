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
typedef  scalar_t__ u8 ;
struct qed_llh_info {scalar_t__ num_ppfid; } ;
struct qed_dev {struct qed_llh_info* p_llh_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,char const*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 

__attribute__((used)) static int qed_llh_shadow_sanity(struct qed_dev *cdev,
				 u8 ppfid, u8 filter_idx, const char *action)
{
	struct qed_llh_info *p_llh_info = cdev->p_llh_info;

	if (ppfid >= p_llh_info->num_ppfid) {
		DP_NOTICE(cdev,
			  "LLH shadow [%s]: using ppfid %d while only %d ppfids are available\n",
			  action, ppfid, p_llh_info->num_ppfid);
		return -EINVAL;
	}

	if (filter_idx >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE) {
		DP_NOTICE(cdev,
			  "LLH shadow [%s]: using filter_idx %d while only %d filters are available\n",
			  action, filter_idx, NIG_REG_LLH_FUNC_FILTER_EN_SIZE);
		return -EINVAL;
	}

	return 0;
}