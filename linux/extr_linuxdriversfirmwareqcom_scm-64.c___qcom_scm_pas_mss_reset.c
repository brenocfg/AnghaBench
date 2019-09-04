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
struct qcom_scm_desc {int* args; int /*<<< orphan*/  arginfo; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a1; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_ARGS (int) ; 
 int /*<<< orphan*/  QCOM_SCM_PAS_MSS_RESET ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_PIL ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_pas_mss_reset(struct device *dev, bool reset)
{
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;
	int ret;

	desc.args[0] = reset;
	desc.args[1] = 0;
	desc.arginfo = QCOM_SCM_ARGS(2);

	ret = qcom_scm_call(dev, QCOM_SCM_SVC_PIL, QCOM_SCM_PAS_MSS_RESET, &desc,
			    &res);

	return ret ? : res.a1;
}