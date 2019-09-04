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
typedef  void* u32 ;
struct qcom_scm_desc {int /*<<< orphan*/  arginfo; void** args; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a1; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_ARGS (int) ; 
 int /*<<< orphan*/  QCOM_SCM_SET_REMOTE_STATE ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_BOOT ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_set_remote_state(struct device *dev, u32 state, u32 id)
{
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;
	int ret;

	desc.args[0] = state;
	desc.args[1] = id;
	desc.arginfo = QCOM_SCM_ARGS(2);

	ret = qcom_scm_call(dev, QCOM_SCM_SVC_BOOT, QCOM_SCM_SET_REMOTE_STATE,
			    &desc, &res);

	return ret ? : res.a1;
}