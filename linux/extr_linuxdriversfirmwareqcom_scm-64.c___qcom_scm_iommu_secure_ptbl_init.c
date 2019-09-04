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
typedef  void* u64 ;
typedef  void* u32 ;
struct qcom_scm_desc {int /*<<< orphan*/  arginfo; void** args; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  QCOM_SCM_ARGS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCOM_SCM_IOMMU_SECURE_PTBL_INIT ; 
 int /*<<< orphan*/  QCOM_SCM_RW ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_MP ; 
 int /*<<< orphan*/  QCOM_SCM_VAL ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_iommu_secure_ptbl_init(struct device *dev, u64 addr, u32 size,
				      u32 spare)
{
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;
	int ret;

	desc.args[0] = addr;
	desc.args[1] = size;
	desc.args[2] = spare;
	desc.arginfo = QCOM_SCM_ARGS(3, QCOM_SCM_RW, QCOM_SCM_VAL,
				     QCOM_SCM_VAL);

	ret = qcom_scm_call(dev, QCOM_SCM_SVC_MP,
			    QCOM_SCM_IOMMU_SECURE_PTBL_INIT, &desc, &res);

	/* the pg table has been initialized already, ignore the error */
	if (ret == -EPERM)
		ret = 0;

	return ret;
}