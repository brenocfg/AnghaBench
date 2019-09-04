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
struct qcom_scm_desc {unsigned int* args; int /*<<< orphan*/  arginfo; int /*<<< orphan*/  member_0; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int dummy; } ;
typedef  unsigned int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_ARGS (int) ; 
 int /*<<< orphan*/  QCOM_SCM_IO_WRITE ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_IO ; 
 int qcom_scm_call (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qcom_scm_desc*,struct arm_smccc_res*) ; 

int __qcom_scm_io_writel(struct device *dev, phys_addr_t addr, unsigned int val)
{
	struct qcom_scm_desc desc = {0};
	struct arm_smccc_res res;

	desc.args[0] = addr;
	desc.args[1] = val;
	desc.arginfo = QCOM_SCM_ARGS(2);

	return qcom_scm_call(dev, QCOM_SCM_SVC_IO, QCOM_SCM_IO_WRITE,
			     &desc, &res);
}