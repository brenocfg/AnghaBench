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
typedef  int u32 ;
struct qed_llh_info {int* ppfid_array; size_t num_ppfid; void** pp_filters; } ;
struct qed_dev {int ppfid_bitmap; struct qed_llh_info* p_llh_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_NUM_PPFID ; 
 int NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_llh_alloc(struct qed_dev *cdev)
{
	struct qed_llh_info *p_llh_info;
	u32 size, i;

	p_llh_info = kzalloc(sizeof(*p_llh_info), GFP_KERNEL);
	if (!p_llh_info)
		return -ENOMEM;
	cdev->p_llh_info = p_llh_info;

	for (i = 0; i < MAX_NUM_PPFID; i++) {
		if (!(cdev->ppfid_bitmap & (0x1 << i)))
			continue;

		p_llh_info->ppfid_array[p_llh_info->num_ppfid] = i;
		DP_VERBOSE(cdev, QED_MSG_SP, "ppfid_array[%d] = %hhd\n",
			   p_llh_info->num_ppfid, i);
		p_llh_info->num_ppfid++;
	}

	size = p_llh_info->num_ppfid * sizeof(*p_llh_info->pp_filters);
	p_llh_info->pp_filters = kzalloc(size, GFP_KERNEL);
	if (!p_llh_info->pp_filters)
		return -ENOMEM;

	size = NIG_REG_LLH_FUNC_FILTER_EN_SIZE *
	    sizeof(**p_llh_info->pp_filters);
	for (i = 0; i < p_llh_info->num_ppfid; i++) {
		p_llh_info->pp_filters[i] = kzalloc(size, GFP_KERNEL);
		if (!p_llh_info->pp_filters[i])
			return -ENOMEM;
	}

	return 0;
}