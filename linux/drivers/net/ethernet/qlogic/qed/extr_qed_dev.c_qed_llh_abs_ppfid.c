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
struct qed_llh_info {size_t num_ppfid; size_t* ppfid_array; } ;
struct qed_dev {struct qed_llh_info* p_llh_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,size_t,size_t) ; 
 int EINVAL ; 

__attribute__((used)) static int qed_llh_abs_ppfid(struct qed_dev *cdev, u8 ppfid, u8 *p_abs_ppfid)
{
	struct qed_llh_info *p_llh_info = cdev->p_llh_info;

	if (ppfid >= p_llh_info->num_ppfid) {
		DP_NOTICE(cdev,
			  "ppfid %d is not valid, available indices are 0..%hhd\n",
			  ppfid, p_llh_info->num_ppfid - 1);
		*p_abs_ppfid = 0;
		return -EINVAL;
	}

	*p_abs_ppfid = p_llh_info->ppfid_array[ppfid];

	return 0;
}